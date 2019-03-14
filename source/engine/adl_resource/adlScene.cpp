#include "adlScene.h"

#include "engine/adl_entities/adlActor.h"
#include "engine/adl_entities/adlPoint_light.h"
#include "engine/adl_entities/adlSun.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_entities/adlEntity.h"
#include "engine/adl_resource/adlTerrain.h"
#include "engine/adl_math/adlMouse_picker.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_renderer/adlDebug_renderer.h"

adlScene::adlScene(const std::string& scene_name)
	:	scene_name_(scene_name),
		sun_(nullptr),
		camera_(nullptr),
		terrain_(nullptr),
		cube_map_(nullptr)
{
}

//adlScene::adlScene(const std::string& scene_name, std::vector<adlEntity_shared_ptr> entities, std::vector<adlActor_shared_ptr> actors, std::vector<adlPoint_light_shared_ptr> point_lights)
//	:	entities_(entities),
//		actors_(actors),
//		point_lights_(point_lights),
//		scene_name_(scene_name),
//		sun_(nullptr),
//		camera_(nullptr),
//		terrain_(nullptr),
//		cube_map_(nullptr)
//{
//}


adlScene::~adlScene()
{
}

void adlScene::update(float dt)
{

	for (auto entity : entities_)
	{
		entity->update(dt);
	}

	camera_->update(dt);
	//sun_->update(dt);
}

void adlScene::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	//renderer->set_lights(point_lights_);
	renderer->set_lights(point_light_components_);
	//renderer->set_sun(sun_);
	renderer->set_camera(camera_);

	if (cube_map_ != nullptr)
	{
		renderer->render(cube_map_);
	}

	for (auto entity : entities_)
	{
		renderer->render(entity);
	}

	renderer->render(sun_);

	renderer->render(terrain_);
}

void adlScene::spawn_entity(adlEntity_shared_ptr entity)
{
	entity->init();
	entities_.push_back(entity);
}

void adlScene::set_sun(adlEntity_shared_ptr sun)
{
	sun_ = sun;
}

void adlScene::set_camera(adlCamera* camera)
{
	camera_ = camera;
}

void adlScene::set_terrain(adlTerrain_shared_ptr terrain)
{
	terrain_ = terrain;
}

void adlScene::set_cube_map(adlCube_map_shared_ptr cube_map)
{
	cube_map_ = cube_map;
}

adlCamera* adlScene::get_camera()
{
	return camera_;
}

adlCube_map_shared_ptr adlScene::get_cube_map()
{
	return cube_map_;
}

std::vector<adlEntity_shared_ptr>& adlScene::get_all_entities()
{
	return entities_;
}

const std::string& adlScene::get_name()
{
	return scene_name_;
}

adlTerrain_shared_ptr adlScene::get_terrain()
{
	return terrain_;
}

void adlScene::add_point_light_entity(adlEntity_shared_ptr entity)
{
	point_light_components_.push_back(entity);
}

void adlScene::remove_point_light_entity(adlEntity_shared_ptr entity)
{
	auto it = std::find(point_light_components_.begin(), point_light_components_.end(), entity);
	if (it != point_light_components_.end()) 
	{
		point_light_components_.erase(it); 
	}
}
