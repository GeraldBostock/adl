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
	void add_actor_to_active_scene(Actor actor);
	void add_light_to_active_scene(Light light);
	void addToScene(Actor actor);
	void addToScene(Light light);
private:
	std::vector<adlEntity> entities_;
	std::vector<Actor> actors_;
	std::vector<Light> lights_;


	adlScene_manager();
};

#endif // adl_scene_manager_h_