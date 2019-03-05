#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlSun.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"

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

	adlEntity_factory* fac = &adlEntity_factory::get();
	adlEntity_shared_ptr entity = fac->construct_entity("test_entity");
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

	Game x(Game());

	return true;
}
