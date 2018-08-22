#include "Game.h"

#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	adlActor_shared_ptr actor = MAKE_SHARED(Test_actor);
	adl_scene_manager->add_actor_to_active_scene(actor);

	adlActor_shared_ptr material_actor = MAKE_SHARED(Material_test);
	adl_scene_manager->add_actor_to_active_scene(material_actor);

	adlActor_shared_ptr wuson = MAKE_SHARED(Material_new_test);
	adl_scene_manager->add_actor_to_active_scene(wuson);

	adlLight_shared_ptr light = MAKE_SHARED(Test_light);
	adl_scene_manager->add_light_to_active_scene(light);

	adl_window->set_mouse_visible(false);

	return true;
}

bool Game::update(float dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key_up(adl_key_f))
	{
		adl_window->toggle_fullscreen();
	}

	return true;
}
