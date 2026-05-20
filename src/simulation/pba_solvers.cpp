#include "pba_solvers.h"

void PBASolver::_bind_methods(){
	godot::ClassDB::bind_method(
		D_METHOD(
			"build",
			"PBAParticleSystem",
			"SolverType",
			"IntegratorType",
			"delta",
			"forces",
			"AABB",
			"cell_size"
		),
		&PBASolver::build
	);
	godot::ClassDB::bind_method(D_METHOD("set_forces", "forces"), &PBASolver::set_forces);
	godot::ClassDB::bind_method(D_METHOD("get_forces"), &PBASolver::get_forces);

	ADD_PROPERTY(
        PropertyInfo(
            Variant::ARRAY,
            "_forces",
            PROPERTY_HINT_ARRAY_TYPE,
            "PBAForce"
        ),
        "set_forces", "get_forces"
    );

	BIND_ENUM_CONSTANT(PARTICLE);
	BIND_ENUM_CONSTANT(SOFT_BODY);
	BIND_ENUM_CONSTANT(RIGID_BODY);
	BIND_ENUM_CONSTANT(SPH);
	BIND_ENUM_CONSTANT(BOID);

	BIND_ENUM_CONSTANT(FORWARD);
	BIND_ENUM_CONSTANT(BACKWARD);
	BIND_ENUM_CONSTANT(LEAP_FROG);
	BIND_ENUM_CONSTANT(SIXTH_ORDER);
}

void PBASolver::solve(){
	_solver_system->solve(_dt);
}

// TO DO -> just get rid of the force system and 
// build the forces into the solver
void PBASolver::build(
	PBAParticleSystem* ps,
	SolverType st,
	IntegratorType integ,
	double dt,
	TypedArray<PBAForce> forces,
	AABB bounds,
	double cell_size
){
	_dt = dt;
	auto dsd = ps->get_dsd();
	auto ch = PBAPhysicsServer::get_singleton()->collision_handler;
	auto rbd_ch = PBAPhysicsServer::get_singleton()->rbd_collision_handler;
	pba::ForceSystem_sp fs = std::make_shared<pba::ForceSystem>();
	for (int i = 0; i < forces.size(); i++){
		Ref<PBAForce> f = forces[i];
		fs->add_force(f->get_pba_force());
	}

	pba::GISolver_sp pos_solver, vel_solver;

	auto ov_maker = [this](AABB bounds, double cell_size){
		pba::AABB pba_aabb = pba::AABB(gvtpba(bounds.position), gvtpba(bounds.get_end()));
		_occupancy_volume = std::make_shared<pba::OccupancyVolume<std::vector<size_t>>>(pba_aabb, cell_size);
	};
	// TODO -> It'd be nice if we could create the solver based on the particle type
	switch (st){
		case PARTICLE: {
			printf("Particle solver created\n");
			fs->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch);
			vel_solver = std::make_shared<pba::AdvanceVelocityWithForces>(dsd, fs);
			break;
		}
		case SOFT_BODY: {
			printf("Soft body solver created\n");
			fs->add_force(std::make_shared<pba::UniformStrutForce>(1.0, 1.0));
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch);
			vel_solver = std::make_shared<pba::AdvanceVelocityWithForces>(dsd, fs);
			break;
		}
		case BOID: {
			printf("BOID solver created\n");
			ov_maker(bounds, cell_size);
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch, _occupancy_volume);
			vel_solver = std::make_shared<pba::AdvanceBoidVelocityWithForces>(dsd, fs, _occupancy_volume);
			break;
		}
		case RIGID_BODY: {
			printf("RBD solver created\n");
			auto dsd_rbd = std::dynamic_pointer_cast<pba::RigidBodyStateData>(dsd);
			fs->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			pos_solver = std::make_shared<pba::AdvanceRotationAndCOMWithCollisions>(dsd_rbd, rbd_ch);
			vel_solver = std::make_shared<pba::AdvanceAngularVelocityAndVelocity>(dsd_rbd, fs);
			break;
		}
		case SPH:{
			printf("SPH solver created\n");
			fs->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			ov_maker(bounds, cell_size);
			auto dsd_sph = std::dynamic_pointer_cast<pba::SPHData>(dsd);
			double h = dsd_sph->h();
			pba::Kernel_sp kernel = std::make_shared<pba::SphSpikyKernel3>(h);
			fs->add_force(std::make_shared<pba::SPHPressureForce>(_occupancy_volume, kernel));
			fs->add_force(std::make_shared<pba::SPHPressureForce>(_occupancy_volume, kernel));
			pos_solver = std::make_shared<pba::SPHPositionSolver>(dsd_sph, ch, _occupancy_volume, kernel);
			vel_solver = std::make_shared<pba::SPHAdvanceVelocityWithForces>(dsd_sph, fs);
			break;
		}
	}

	_compose(pos_solver, vel_solver, integ);
	PBAPhysicsServer::get_singleton()->register_solver(_solver_system);
}

void PBASolver::_compose(pba::GISolver_sp a, pba::GISolver_sp b, IntegratorType integ){
	switch (integ){
		case FORWARD: {
			_solver_system = std::make_shared<pba::GISolverSystem>();
			_solver_system->add_solver(a, _dt);
			_solver_system->add_solver(b, _dt);
			break;
		}
		case BACKWARD:{
			_solver_system = std::make_shared<pba::GISolverSystem>();
			_solver_system->add_solver(b, _dt);
			_solver_system->add_solver(a, _dt);
			break;
		}
		case LEAP_FROG:{
			_solver_system = std::make_shared<pba::GISolverSystem>();
			_solver_system->add_solver(std::make_shared<pba::GISolverLeapfrog>(a, b), _dt);
			break;
		}
		case SIXTH_ORDER:
			_solver_system = std::make_shared<pba::GISolverSystem>();
			auto lf = std::make_shared<pba::GISolverLeapfrog>(a, b);
			auto so = std::make_shared<pba::GISolverSixthOrder>(lf);
			_solver_system->add_solver(so, _dt);
			break;
	}
}
