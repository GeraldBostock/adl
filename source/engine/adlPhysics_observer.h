#ifndef adl_physics_observer_h__
#define adl_physics_observer_h__

#include "adlShared_types.h"
#include "adl_math/adlMath.h"

class adlPhysics_observer
{
public:
	virtual ~adlPhysics_observer() {}
	virtual void on_collision_start(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2) = 0;
	virtual void on_collision_end(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2) = 0;
	virtual void on_terrain_collision_start(adlEntity_shared_ptr entity, const adlVec3& collision_point) = 0;
	virtual void on_terrain_collision_end(adlEntity_shared_ptr entity) = 0;
	virtual void on_terrain_mouse_ray_collision(const adlVec3& collision_point) = 0;
};

#endif //adl_physics_observer_h__