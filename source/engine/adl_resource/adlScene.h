#ifndef adl_scene_h__
#define adl_scene_h__

#include <vector>

#include "engine/adlShared_types.h"
#include "engine/adl_renderer/adlCamera.h"

class adlScene
{
public:
	adlScene(const std::string& scene_name);
	//adlScene(const std::string& scene_name, std::vector<adlEntity_shared_ptr> entities, std::vector<adlActor_shared_ptr> actors, std::vector<adlPoint_light_shared_ptr> point_lights);
	~adlScene();

	void update(float dt);
	void render();

	void spawn_entity(adlEntity_shared_ptr entity);
	void set_sun(adlEntity_shared_ptr sun);
	void set_camera(adlCamera* camera);
	void set_terrain(adlTerrain_shared_ptr terrain);
	void set_cube_map(adlCube_map_shared_ptr cube_map);
	void add_point_light_entity(adlEntity_shared_ptr entity);
	void remove_point_light_entity(adlEntity_shared_ptr entity);

	adlCamera* get_camera();
	adlTerrain_shared_ptr get_terrain();
	adlCube_map_shared_ptr get_cube_map();
	std::vector<adlEntity_shared_ptr>& get_all_entities();

	const std::string& get_name();

private:

	std::string scene_name_;

	std::vector<adlEntity_shared_ptr> entities_;
	std::vector<adlEntity_shared_ptr> point_light_components_;

	adlEntity_shared_ptr sun_;
	adlCamera* camera_;
	adlTerrain_shared_ptr terrain_;
	adlCube_map_shared_ptr cube_map_;
};

#endif // adl_scene_h__