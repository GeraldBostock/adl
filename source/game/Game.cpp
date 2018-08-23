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
	adl_scene_manager->add_to_active_scene(actor);

	adlActor_shared_ptr someActor = MAKE_SHARED(adlActor);
	someActor->setPosition(adlVec3(-15.0, -5.0f, 15.0f));
	someActor->setRotation(adlVec3(0.0f));
	someActor->setScale(adlVec3(1.0f));
	someActor->setMaterial(adl_rm->get_material("silver"));
	someActor->setModel(adl_rm->get_model("mountain"));
	adl_scene_manager->spawnActor(someActor);

	adlActor_shared_ptr material_actor = MAKE_SHARED(Material_test);
	adl_scene_manager->add_to_active_scene(material_actor);

	adlActor_shared_ptr wuson = MAKE_SHARED(Material_new_test);
	adl_scene_manager->add_to_active_scene(wuson);

	adlLight_shared_ptr light = MAKE_SHARED(Test_light);
	adl_scene_manager->add_to_active_scene(light);

	for (int i = 0; i < 20; i++)
	{
		adlActor_shared_ptr multi_actor = MAKE_SHARED(Material_test);
		adl_scene_manager->spawn_actor(multi_actor, adlVec3(i * 3, 0, 0));
	}

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
