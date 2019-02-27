#ifndef physics_listener_h__
#define physics_listener_h__

#include "../engine/adlPhysics_observer.h" 
#include "engine/adl_entities/adlActor.h"
#include "engine/adl_resource/adlResource_manager.h"

class Physics_listener : public adlPhysics_observer
{
public:
	Physics_listener() {};
	~Physics_listener() {};

	virtual void on_collision_start(adlActor_shared_ptr actor1, adlActor_shared_ptr actor2) override
	{
	}

	virtual void on_collision_end(adlActor_shared_ptr actor1, adlActor_shared_ptr actor2) 
	{
	}

	virtual void on_terrain_collision_start(adlActor_shared_ptr actor, const adlVec3& collision_point) 
	{
	}

	virtual void on_terrain_collision_end(adlActor_shared_ptr actor) 
	{
	}

	virtual void on_terrain_mouse_ray_collision(const adlVec3& collision_point) 
	{
	}
};

#endif //physics_listener_h__