#ifndef adl_physics_observer_h__
#define adl_physics_observer_h__

#include "adlShared_types.h"
#include "adl_math/adlMath.h"

class adlPhysics_observer
{
public:
	virtual ~adlPhysics_observer() {}
	virtual void on_collision_start(adlActor_shared_ptr actor1, adlActor_shared_ptr actor2) = 0;
	virtual void on_collision_end(adlActor_shared_ptr actor1, adlActor_shared_ptr actor2) = 0;
	virtual void on_terrain_collision_start(adlActor_shared_ptr actor, const adlVec3& collision_point) = 0;
	virtual void on_terrain_collision_end(adlActor_shared_ptr actor) = 0;
	virtual void on_terrain_mouse_ray_collision(const adlVec3& collision_point) = 0;
};

#endif //adl_physics_observer_h__