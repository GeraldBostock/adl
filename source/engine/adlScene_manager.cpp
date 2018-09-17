#include "adlScene_manager.h"

#include "adl_renderer/adlRender_manager.h"
#include "adl_debug/imgui/imgui.h"
#include "engine/adlMemory.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlInput.h"


adlScene_manager::adlScene_manager()
{
}

adlScene_shared_ptr adlScene_manager::create_empty_scene(const std::string& scene_name)
{
	adlScene_shared_ptr new_scene = MAKE_SHARED(adlScene, scene_name);

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adl_rm->add_new_scene(scene_name, new_scene);

	return new_scene;
}

void adlScene_manager::set_active_scene(adlScene_shared_ptr scene)
{
	active_scene_ = scene;
	adlRender_manager* renderer = &adlRender_manager::get();
	renderer->set_sun(active_scene_->get_sun());
	renderer->set_lights(active_scene_->get_all_point_lights());
	camera_ = scene->get_camera();
}

void adlScene_manager::update(float dt)
{
	adlInput* input = &adlInput::get();
	if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_s))
	{

	}

	if (active_scene_ != nullptr)
	{
		active_scene_->update(dt);
	}
}

void adlScene_manager::render()
{
	if (active_scene_ != nullptr)
	{
		active_scene_->render();
	}
}

void adlScene_manager::add_to_scene(adlEntity_shared_ptr entity)
{
	entity->init();
	entities_.push_back(entity);
}

void adlScene_manager::addToScene(adlEntity_shared_ptr entity)
{
	add_to_scene(entity);
}

void adlScene_manager::add_to_scene(adlActor_shared_ptr actor)
{
	actor->init();
	actors_.push_back(actor);
}

void adlScene_manager::addToScene(adlActor_shared_ptr actor)
{
	add_to_scene(actor);
}

void adlScene_manager::set_sun(adlSun_shared_ptr sun)
{
	sun->init();
	active_scene_->set_sun(sun);
	adlRender_manager* renderer = &adlRender_manager::get();
	renderer->set_sun(sun);
}

void adlScene_manager::setSun(adlSun_shared_ptr sun)
{
	set_sun(sun);
}

adlActor_shared_ptr adlScene_manager::spawn_actor(const std::string& actor_name, adlVec3 position/* = adlVec3(0.0f)*/, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	adlEntity_factory* factory = &adlEntity_factory::get();
	adlActor* actor = (adlActor*)factory->construct_actor(actor_name);
	adlActor_shared_ptr actor_shared(actor);

	active_scene_->spawn_actor(actor_shared, position, rotation, scale);

	return actor_shared;
}

void adlScene_manager::spawn_actor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	actor->init();
	actors_.push_back(actor);
	actor->set_position(position);
	actor->set_rotation(rotation);
	actor->set_scale(scale);
}

void adlScene_manager::spawnActor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	spawn_actor(actor, position, rotation, scale);
}

void adlScene_manager::spawn_light(const std::string& light_name, adlVec3 position/* = adlVec3(0.0f)*/, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	adlEntity_factory* factory = &adlEntity_factory::get();
	adlPoint_light* light = (adlPoint_light*)factory->construct_light(light_name);
	adlPoint_light_shared_ptr shared_light(light);

	active_scene_->spawn_point_light(shared_light, position, rotation, scale);
}

void adlScene_manager::addPointLightToScene(adlPoint_light_shared_ptr point_light)
{
	add_point_light_scene(point_light);
}

void adlScene_manager::add_point_light_scene(adlPoint_light_shared_ptr point_light)
{
	point_light->init();
	point_lights_.push_back(point_light);
}

std::vector<adlEntity_shared_ptr>& adlScene_manager::get_all_entities()
{
	return active_scene_->get_all_entities();
}

std::vector<adlActor_shared_ptr>& adlScene_manager::get_all_actors()
{
	return active_scene_->get_all_actors();
}

std::vector<adlPoint_light_shared_ptr>& adlScene_manager::get_all_point_lights()
{
	return active_scene_->get_all_point_lights();
}

adlSun_shared_ptr adlScene_manager::get_sun()
{
	return active_scene_->get_sun();
}

adlCamera* adlScene_manager::getCamera()
{
	return get_camera();
}

adlCamera* adlScene_manager::get_camera()
{
	return active_scene_->get_camera();
}

void adlScene_manager::set_camera(adlCamera* camera)
{
	active_scene_->set_camera(camera);
}

adlScene_shared_ptr adlScene_manager::get_active_scene()
{
	return active_scene_;
}