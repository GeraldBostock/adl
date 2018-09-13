#ifndef adl_scene_manager_h__
#define adl_scene_manager_h__

#include "adl_entities/adlEntity.h"
#include "adl_entities/adlActor.h"
#include "adl_entities/adlLight.h"
#include "adl_entities/adlPoint_light.h"
#include "adl_entities/adlSun.h"
#include "adl_renderer/adlCamera.h"
#include "engine/adl_resource/adlScene.h"
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

	adlScene_shared_ptr create_empty_scene(const std::string& scene_name);
	void set_active_scene(adlScene_shared_ptr scene);

	void add_to_scene(adlEntity_shared_ptr entity);
	void addToScene(adlEntity_shared_ptr entity);

	void add_to_scene(adlActor_shared_ptr actor);
	void addToScene(adlActor_shared_ptr actor);

	void set_sun(adlSun_shared_ptr sun);
	void setSun(adlSun_shared_ptr sun);

	void set_camera(adlCamera* camera);

	void addPointLightToScene(adlPoint_light_shared_ptr point_light);
	void add_point_light_scene(adlPoint_light_shared_ptr point_light);

	adlActor_shared_ptr spawn_actor(const std::string& actor_name, adlVec3 position = adlVec3(0.0f), adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	void spawn_light(const std::string& light_name, adlVec3 position = adlVec3(0.0f), adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));

	void spawn_actor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	void spawnActor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	

	std::vector<adlEntity_shared_ptr>& get_all_entities();
	std::vector<adlActor_shared_ptr>& get_all_actors();
	std::vector<adlPoint_light_shared_ptr>& get_all_point_lights();
	adlSun_shared_ptr get_sun();

	adlCamera* getCamera();
	adlCamera* get_camera();

private:
	std::vector<adlEntity_shared_ptr> entities_;
	std::vector<adlActor_shared_ptr> actors_;
	std::vector<adlSun_shared_ptr> suns_;
	std::vector<adlPoint_light_shared_ptr> point_lights_;

	adlSun_shared_ptr sun_;
	adlCamera* camera_;

	adlScene_shared_ptr active_scene_ = nullptr;

	adlScene_manager();
};

#endif // adl_scene_manager_h_