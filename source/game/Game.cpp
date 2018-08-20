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
	/*adlActor_shared_ptr */actor = MAKE_SHARED(Test_actor);
	adl_scene_manager->add_actor_to_active_scene(actor);

	adlLight_shared_ptr light = MAKE_SHARED(Test_light);
	adl_scene_manager->add_light_to_active_scene(light);

	adl_window->set_mouse_visible(false);

	/*adlLight* light = ADL_NEW(adlLight, adl_rm->get_model("cube"), adlColor::WHITE);
	adlTransform transform = adlTransform::identity();
	transform.o = adlVec3(0, 2, 0);
	light->set_frame(transform);
	adl_renderer->set_light(light);*/
	return true;
}

bool Game::update(float dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	return true;
}
