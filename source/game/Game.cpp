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
	/*Actor actor = MAKE_SHARED(Test_actor);
	adl_scene_manager->add_actor_to_active_scene(actor);*/

	/*Actor material_actor = MAKE_SHARED(Material_test);
	adl_scene_manager->add_actor_to_active_scene(material_actor);*/

	Actor base = MAKE_SHARED(Test_actor);
	base->setModel("landscape");
	base->setMaterial(adl_rm->get_material("emerald"));
	base->setTransform(adlVec3(-8.0f, -5.0f, 0.0f), adlVec3(0.0f), adlVec3(1.0f));
	adl_scene_manager->addToScene(base);

	Actor car = MAKE_SHARED(Test_actor);
	car->setModel("mountain");
	car->setMaterial(adl_rm->get_material("chrome"));
	car->setTransform(adlVec3(-20.0f, -5.0f, 20.0f), adlVec3(0.0f), adlVec3(1.0f));
	adl_scene_manager->addToScene(car);

	Actor wuson = MAKE_SHARED(Material_new_test);
	adl_scene_manager->addToScene(wuson);

	Light light = MAKE_SHARED(Test_light);
	adl_scene_manager->addToScene(light);

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
