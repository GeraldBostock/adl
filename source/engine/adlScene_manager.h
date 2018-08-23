#ifndef adl_scene_manager_h__
#define adl_scene_manager_h__

#include "adl_entities/adlEntity.h"
#include "adl_entities/adlActor.h"
#include "adl_entities/adlLight.h"
#include "adlShared_types.h"

#include <vector>

class adlScene_manager
{
public:

	static adlScene_manager& get()
	{
		static adlScene_manager instance;
		return instance;
	}

	void update(float dt);
	void render();

	void add_entity_to_active_scene(adlEntity entity);
	void add_actor_to_active_scene(adlActor_shared_ptr actor);
	void add_light_to_active_scene(adlLight_shared_ptr light);

	void spawn_actor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
private:
	std::vector<adlEntity> entities_;
	std::vector<adlActor_shared_ptr> actors_;
	std::vector<adlLight_shared_ptr> lights_;


	adlScene_manager();
};

#endif // adl_scene_manager_h_