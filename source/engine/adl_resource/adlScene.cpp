#include "adlScene.h"

#include "engine/adl_entities/adlActor.h"
#include "engine/adl_entities/adlPoint_light.h"
#include "engine/adl_entities/adlSun.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_entities/adlEntity.h"
#include "engine/adl_resource/adlTerrain.h"

adlScene::adlScene(const std::string& scene_name)
	:	scene_name_(scene_name),
		sun_(nullptr),
		camera_(nullptr),
		terrain_(nullptr),
		cube_map_(nullptr)
{

}

adlScene::adlScene(const std::string& scene_name, std::vector<adlEntity_shared_ptr> entities, std::vector<adlActor_shared_ptr> actors, std::vector<adlPoint_light_shared_ptr> point_lights)
	:	entities_(entities),
		actors_(actors),
		point_lights_(point_lights),
		scene_name_(scene_name),
		sun_(nullptr),
		camera_(nullptr),
		terrain_(nullptr),
		cube_map_(nullptr)
{
}


adlScene::~adlScene()
{
}

void adlScene::update(float dt)
{
	for (auto entity : entities_)
	{
		entity->update(dt);
	}

	for (auto actor : actors_)
	{
		actor->update(dt);
	}

	camera_->update(dt);
	sun_->update(dt);

	for (auto light : point_lights_)
	{
		light->update(dt);
	}
}

void adlScene::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	renderer->set_lights(point_lights_);
	renderer->set_camera(camera_);

	renderer->render(cube_map_);

	for (auto actor : actors_)
	{
		renderer->render(actor);
	}

	renderer->render(sun_);

	for (auto light : point_lights_)
	{
		renderer->render(light);
	}

	renderer->render(terrain_);
}

void adlScene::spawn_entity(adlEntity_shared_ptr entity)
{
	entity->init();
	entities_.push_back(entity);
}

void adlScene::spawn_actor(adlActor_shared_ptr actor, adlVec3 position/* = adlVec3(0.0f)*/, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	actor->init();
	actor->set_position(position);
	actor->set_rotation(rotation);
	actor->set_scale(scale);
	actors_.push_back(actor);
}

void adlScene::spawn_point_light(adlPoint_light_shared_ptr point_light, adlVec3 position/* = adlVec3(0.0f)*/, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	point_light->init();
	point_light->set_position(position);
	point_light->set_rotation(rotation);
	point_light->set_scale(scale);
	point_lights_.push_back(point_light);
}

void adlScene::set_sun(adlSun_shared_ptr sun)
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

adlSun_shared_ptr adlScene::get_sun()
{
	return sun_;
}

adlCube_map_shared_ptr adlScene::get_cube_map()
{
	return cube_map_;
}

std::vector<adlEntity_shared_ptr>& adlScene::get_all_entities()
{
	return entities_;
}

std::vector<adlActor_shared_ptr>& adlScene::get_all_actors()
{
	return actors_;
}

std::vector<adlPoint_light_shared_ptr>& adlScene::get_all_point_lights()
{
	return point_lights_;
}

const std::string& adlScene::get_name()
{
	return scene_name_;
}

adlTerrain_shared_ptr adlScene::get_terrain()
{
	return terrain_;
}
