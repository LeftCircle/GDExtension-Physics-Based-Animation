#include "pba_solvers.h"

void PBASolver::_bind_methods(){
	godot::ClassDB::bind_method(
		D_METHOD("build", "PBAParticleSystem", "SolverType", "IntegratorType", "AABB", "cell_size"),
		&PBASolver::build
	);
}

void PBASolver::solve(){

}

// TO DO -> just get rid of the force system and 
// build the forces into the solver
void PBASolver::build(
	PBAParticleSystem* ps,
	SolverType st,
	IntegratorType integ, 
	double dt,
	AABB bounds,
	double cell_size
){
	_dt = dt;
	auto dsd = ps->get_dsd();
	auto ch = PBAPhysicsServer::get_singleton()->collision_handler;
	auto rbd_ch = PBAPhysicsServer::get_singleton()->rbd_collision_handler;
	pba::ForceSystem_sp forces = std::make_shared<pba::ForceSystem>();
	
	pba::GISolver_sp pos_solver, vel_solver;

	auto ov_maker = [this](AABB bounds, double cell_size){
		pba::AABB pba_aabb = pba::AABB(gvtpba(bounds.position), gvtpba(bounds.get_end()));
		_occupancy_volume = std::make_shared<pba::OccupancyVolume<std::vector<size_t>>>(pba_aabb, cell_size);
	};
	// TODO -> It'd be nice if we could create the solver based on the particle type
	switch (st){
		case PARTICLE:
			forces->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch);
			vel_solver = std::make_shared<pba::AdvanceVelocityWithForces>(dsd, forces);
			break;
		case SOFT_BODY:
			forces->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			forces->add_force(std::make_shared<pba::UniformStrutForce>(1.0, 1.0));
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch);
			vel_solver = std::make_shared<pba::AdvanceVelocityWithForces>(dsd, forces);
			break;
		case BOID:
			ov_maker(bounds, cell_size);
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch, _occupancy_volume);
			vel_solver = std::make_shared<pba::AdvanceBoidVelocityWithForces>(dsd, forces, _occupancy_volume);
			break;
		case RIGID_BODY:
			forces->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			pos_solver = std::make_shared<pba::AdvanceRotationAndCOMWithCollisions>(dsd, rbd_ch);
			vel_solver = std::make_shared<pba::AdvanceAngularVelocityAndVelocity>(dsd, forces);
			break;
		case SPH:
			forces->add_force(std::make_shared<pba::SimpleGravityForce>(pba::Vector(0, -9.8, 0)));
			ov_maker(bounds, cell_size);
			auto dsd_sph = std::dynamic_pointer_cast<pba::SPHData>(dsd);
			double h = dsd_sph->h();
			pba::Kernel_sp kernel = std::make_shared<pba::SphSpikyKernel3>(h);
			forces->add_force(std::make_shared<pba::SPHPressureForce>(_occupancy_volume, kernel));
			forces->add_force(std::make_shared<pba::SPHPressureForce>(_occupancy_volume, kernel));
			pos_solver = std::make_shared<pba::SPHPositionSolver>(dsd, ch, _occupancy_volume);
			vel_solver = std::make_shared<pba::SPHAdvanceVelocityWithForces>(dsd, forces);
	}

	_compose(pos_solver, vel_solver, integ);
}

void PBASolver::_compose(pba::GISolver_sp a, pba::GISolver_sp b, IntegratorType integ){
	switch (integ){
		case FORWARD:
			_solver_system = std::make_shared<pba::GISolverSystem>();
			_solver_system->add_solver(a, _dt);
			_solver_system->add_solver(b, _dt);
			break;
		case BACKWARD:
			_solver_system = std::make_shared<pba::GISolverSystem>();
			_solver_system->add_solver(b, _dt);
			_solver_system->add_solver(a, _dt);
		case LEAP_FROG:
			_solver_system = std::make_shared<pba::GISolverSystem>();
			_solver_system->add_solver(std::make_shared<pba::GISolverLeapfrog>(a, b), _dt);
			break;
		case SIXTH_ORDER:
			_solver_system = std::make_shared<pba::GISolverSystem>();
			auto lf = std::make_shared<pba::GISolverLeapfrog>(a, b);
			auto so = std::make_shared<pba::GISolverSixthOrder>(lf);
			_solver_system->add_solver(so, _dt);
			break;
	}
}
