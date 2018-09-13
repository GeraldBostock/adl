#ifndef adl_scene_h__
#define adl_scene_h__

#include <vector>

#include "engine/adlShared_types.h"
#include "engine/adl_renderer/adlCamera.h"

class adlScene
{
public:
	adlScene(const std::string& scene_name);
	adlScene(const std::string& scene_name, std::vector<adlEntity_shared_ptr> entities, std::vector<adlActor_shared_ptr> actors, std::vector<adlPoint_light_shared_ptr> point_lights);
	~adlScene();

	void update(float dt);
	void render();

	void spawn_entity(adlEntity_shared_ptr entity);
	void spawn_actor(adlActor_shared_ptr actor, adlVec3 position = adlVec3(0.0f), adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	void spawn_point_light(adlPoint_light_shared_ptr point_light, adlVec3 position = adlVec3(0.0f), adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	void set_sun(adlSun_shared_ptr sun);
	void set_camera(adlCamera* camera);

	adlCamera* get_camera();
	adlSun_shared_ptr get_sun();
	std::vector<adlEntity_shared_ptr>& get_all_entities();
	std::vector<adlActor_shared_ptr>& get_all_actors();
	std::vector<adlPoint_light_shared_ptr>& get_all_point_lights();

	const std::string& get_name();

private:

	std::string scene_name_;

	std::vector<adlEntity_shared_ptr> entities_;
	std::vector<adlActor_shared_ptr> actors_;
	std::vector<adlPoint_light_shared_ptr> point_lights_;

	adlSun_shared_ptr sun_;
	adlCamera* camera_;
};

#endif // adl_scene_h__