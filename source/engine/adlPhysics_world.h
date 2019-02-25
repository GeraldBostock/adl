#ifndef adl_physics_world_h__
#define adl_physics_world_h__

#include "engine/adlShared_types.h"

class adlPhysics_world
{
public:
	adlPhysics_world();
	~adlPhysics_world();

	void add_collision_actor(adlActor_shared_ptr actor);
};

#endif //adl_physics_world_h__