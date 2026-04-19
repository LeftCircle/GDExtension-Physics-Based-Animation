#include "pba_solvers.h"

void PBASolver::_bind_methods(){

}

void PBASolver::solve(){

}

// TO DO -> just get rid of the force system and 
// build the forces into the solver
void PBASolver::build(
	PBAParticleSystem* ps,
	PBAForceSystem* fs,
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
	auto forces = fs->get_force_system();
	pba::GISolver_sp pos_solver, vel_solver;

	auto ov_maker = [this](AABB bounds, double cell_size){
		pba::AABB pba_aabb = pba::AABB(gvtpba(bounds.position), gvtpba(bounds.get_end()));
		_occupancy_volume = std::make_shared<pba::OccupancyVolume<std::vector<size_t>>>(pba_aabb, cell_size);
	};
	// TODO -> It'd be nice if we could create the solver based on the particle type
	switch (st){
		case PARTICLE:
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch);
			vel_solver = std::make_shared<pba::AdvanceVelocityWithForces>(dsd, forces);
			break;
		case SOFT_BODY:
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch);
			vel_solver = std::make_shared<pba::AdvanceVelocityWithForces>(dsd, forces);
			break;
		case BOID:
			ov_maker(bounds, cell_size);
			pos_solver = std::make_shared<pba::PartialSolverAdvancePosition>(dsd, ch, _occupancy_volume);
			vel_solver = std::make_shared<pba::AdvanceBoidVelocityWithForces>(dsd, forces, _occupancy_volume);
			break;
		case RIGID_BODY:
			pos_solver = std::make_shared<pba::AdvanceRotationAndCOMWithCollisions>(dsd, rbd_ch);
			vel_solver = std::make_shared<pba::AdvanceAngularVelocityAndVelocity>(dsd, forces);
			break;
		case SPH:
			ov_maker(bounds, cell_size);
			pos_solver = std::make_shared<pba::SPHPositionSolver>(dsd, ch, _occupancy_volume);
			vel_solver = std::make_shared<pba::SPHAdvanceVelocityWithForces>(dsd, forces)
			
	}
}

// void PBAAdvancePositionSolver::_bind_methods() {
// 	godot::ClassDB::bind_method(
//         D_METHOD("init", "PBAParticleSystem"),
//         &PBAAdvancePositionSolver::init
//     );
// }

// void PBAAdvancePositionSolver::init(PBAParticleSystem* ps){
//     pba::CollisionHandler_sp ch = PBAPhysicsServer::get_singleton()->collision_handler;
//     _solver = std::make_shared<pba::PartialSolverAdvancePosition>(ps->get_dsd(), ch);
// }

// void PBAAdvanceVelocityWithForces::_bind_methods() {
//     godot::ClassDB::bind_method(
//         D_METHOD("init", "PBAParticles", "PBAForceSystem"),
//         &PBAAdvanceVelocityWithForces::init
//     );
// }

// void PBAAdvanceVelocityWithForces::init(PBAParticleSystem* ps, PBAForceSystem* fs){
//     _solver = std::make_shared<pba::AdvanceVelocityWithForces>(ps->get_dsd(), fs->get_force_system());
// }