#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "example_class.h"
#include "pba_particle_system.h"
#include "pba_collision_object.h"
#include "pba_physics_server.h"
#include "pba_solvers.h"
#include "pba_resources.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(ExampleClass);
	GDREGISTER_CLASS(PBAParticleSystem);
	GDREGISTER_CLASS(PBACollisionPlane);
	GDREGISTER_CLASS(PBACollisionSurface);
	GDREGISTER_CLASS(PBASolver);
	GDREGISTER_CLASS(PBASoftTriangle);
	GDREGISTER_CLASS(PBAEdge);
	GDREGISTER_CLASS(PBAForce);
	GDREGISTER_ABSTRACT_CLASS(PBACollisionObject);

	GDREGISTER_ABSTRACT_CLASS(PBAPhysicsServer);

	PBAPhysicsServer* server = memnew(PBAPhysicsServer);
	Engine::get_singleton()->register_singleton("PBAPhysicsServer", server);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	Engine::get_singleton()->unregister_singleton("PBAPhysicsServer");
	memdelete(PBAPhysicsServer::get_singleton());
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT physics_based_animation_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}