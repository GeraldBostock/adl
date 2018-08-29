#ifndef adl_scene_manager_h__
#define adl_scene_manager_h__

#include "adl_entities/adlEntity.h"
#include "adl_entities/adlActor.h"
#include "adl_entities/adlLight.h"
#include "adl_entities/adlPoint_light.h"
#include "adl_entities/adlSun.h"
#include "adlShared_types.h"
#include "engine/adl_debug/adlLight_editor.h"

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

	void add_to_scene(adlEntity entity);
	void addToScene(adlEntity entity);

	void add_to_scene(adlActor_shared_ptr actor);
	void addToScene(adlActor_shared_ptr actor);

	void set_sun(adlSun_shared_ptr sun);
	void setSun(adlSun_shared_ptr sun);

	void addPointLightToScene(adlPoint_light_shared_ptr point_light);
	void add_point_light_scene(adlPoint_light_shared_ptr point_light);

	void spawn_actor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	void spawnActor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
private:
	std::vector<adlEntity> entities_;
	std::vector<adlActor_shared_ptr> actors_;
	std::vector<adlSun_shared_ptr> suns_;
	std::vector<adlPoint_light_shared_ptr> point_lights_;

	adlSun_shared_ptr sun_;

	adlScene_manager();

	adlLight_editor* light_editor_;
};

#endif // adl_scene_manager_h_