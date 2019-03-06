#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlSun.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"
#include "engine/adl_entities/adlPhysics_component.h"

Game::Game()
{

}

Game::~Game()
{

}


bool Game::init()
{
	adlTransform_component tc;
	adlRender_component r;
	adlPhysics_component p;
	adlScene_shared_ptr scene = adl_scene_manager->create_empty_scene("new_scene");
	adl_scene_manager->set_active_scene(scene);

	scene->set_cube_map(adl_rm->get_cube_map("default"));
	
	listener_ = ADL_NEW(Physics_listener);
	adl_scene_manager->add_physics_observer(listener_);

	adlSun_shared_ptr sun = MAKE_SHARED(adlSun);
	sun->set_position(adlVec3(0, 300, 20));
	adl_scene_manager->setSun(sun);

	adlPoint_light_shared_ptr point_light = MAKE_SHARED(adlPoint_light);
	point_light->set_name("Light_#1");

	adlCamera* camera = ADL_NEW(adlCamera);
	camera->set_camera_type(ct_god_mode);
	camera->init();

	adl_scene_manager->set_camera(camera);

	adl_window->set_mouse_visible(false);

	scene->set_sun(sun);
	scene->set_camera(camera);

	adlTerrain_shared_ptr terrain = adl_rm->get_terrain("test_terrain");
	adl_scene_manager->set_terrain(terrain);

	entity = adl_scene_manager->add_entity_to_scene("test_entity");
	adlEntity_shared_ptr entity1 = adl_scene_manager->add_entity_to_scene("test_entity");

	std::shared_ptr<adlTransform_component> component = std::shared_ptr(entity->get_component<adlTransform_component>("adlTransform_component"));

	return true;
}

bool Game::update(float dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key(adl_key_left_alt) && adl_input->get_key_down(adl_key_f))
	{
		adl_window->toggle_fullscreen();
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key(adl_key_y))
	{
		if (entity->has_component("adlPhysics_component"))
		{
			std::shared_ptr<adlPhysics_component> component = std::shared_ptr(entity->get_component<adlPhysics_component>("adlPhysics_component"));
			component->apply_force(adlVec3(0, 0, 1), 2);
		}
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_h))
	{
		if (entity->has_component("adlPhysics_component"))
		{
			entity->remove_component("adlPhysics_component");
		}
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_n))
	{
		if (!entity->has_component("adlPhysics_component"))
		{
			adlEntity_factory* fac = &adlEntity_factory::get();
			fac->add_component_to_entity(entity, "adlPhysics_component");
		}
	}

	return true;
}
