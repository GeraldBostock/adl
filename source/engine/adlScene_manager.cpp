#include "adlScene_manager.h"

#include "adl_renderer/adlRender_manager.h"
#include "adl_debug/imgui/imgui.h"
#include "engine/adlMemory.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlInput.h"
#include "engine/adl_math/adlMouse_picker.h"
#include "adl_resource/adlTerrain.h"


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
	camera_ = scene->get_camera();
	if (camera_ != nullptr)
	{
		camera_->set_paused(true);
	}
}

void adlScene_manager::set_physics(adlIPhysics* physics)
{
	physics_ = std::shared_ptr<adlIPhysics>(physics);
}

void adlScene_manager::update(float dt)
{
	adlInput* input = &adlInput::get();
	adlMouse_picker* picker = &adlMouse_picker::get();

	physics_->get_all_raycast_hits(picker->get_mouse_ray());
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

void adlScene_manager::add_plane()
{
	physics_->add_static_plane();
}

adlEntity_shared_ptr adlScene_manager::add_entity_to_scene(const std::string& entity_name)
{
	adlEntity_factory* entity_factory = &adlEntity_factory::get();
	adlEntity_shared_ptr entity = entity_factory->construct_entity(entity_name);

	if (entity)
	{
		entities_.push_back(entity);
		active_scene_->spawn_entity(entity);
	}

	return entity;
}

void adlScene_manager::set_terrain(adlTerrain_shared_ptr terrain)
{
	active_scene_->set_terrain(terrain);
	physics_->add_terrain(terrain->get_heightfield());
}

std::vector<adlEntity_shared_ptr>& adlScene_manager::get_all_entities()
{
	return active_scene_->get_all_entities();
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

void adlScene_manager::set_sun(adlEntity_shared_ptr sun)
{
	adl_assert(sun);
	if (!sun)
	{
		return;
	}

	if (!sun->has_component("adlSun_component"))
	{
		adlLogger* logger = &adlLogger::get();
		logger->log_warning("Entity " + sun->get_name() + " has no sun component. It can't be the sun.");
	}
	else
	{
		active_scene_->set_sun(sun);
	}
}

void adlScene_manager::light_component_added(adlEntity_shared_ptr entity, const std::string& component_name)
{
	if (component_name == "adlSun_component")
	{
		sun_components_.push_back(entity);
	}
	else if (component_name == "adlPoint_light_component")
	{
		point_light_components_.push_back(entity);
		active_scene_->add_point_light_entity(entity);
	}
}

void adlScene_manager::light_component_removed(adlEntity_shared_ptr entity, const std::string& component_name)
{
	if (component_name == "adlSun_component")
	{
		sun_components_.push_back(entity);
	}
	else if (component_name == "adlPoint_light_component")
	{
		active_scene_->remove_point_light_entity(entity);
	}
}