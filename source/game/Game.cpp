#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlSun.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	adlActor_shared_ptr actor = MAKE_SHARED(Test_actor);
	adl_scene_manager->addToScene(actor);

	adlActor_shared_ptr landscape = MAKE_SHARED(Test_actor);
	adl_scene_manager->addToScene(landscape);
	landscape->set_position(adlVec3(0, -15, 20));
	landscape->setModel(adl_rm->getModel("landscape"));

	adlActor_shared_ptr material_actor = MAKE_SHARED(Material_test);
	adl_scene_manager->addToScene(material_actor);

	adlActor_shared_ptr wuson = MAKE_SHARED(Material_new_test);
	adl_scene_manager->addToScene(wuson);

	adlSun_shared_ptr sun = MAKE_SHARED(adlSun);
	adl_scene_manager->setSun(sun);

	adlPoint_light_shared_ptr point_light = MAKE_SHARED(adlPoint_light);
	adl_scene_manager->addPointLightToScene(point_light);

	adlPoint_light_shared_ptr second_light = MAKE_SHARED(adlPoint_light);
	adl_scene_manager->addPointLightToScene(second_light);
	second_light->set_position(adlVec3(0, 0, 20));

	for (int i = 0; i < 20; i++)
	{
		adlActor_shared_ptr multi_actor = MAKE_SHARED(Material_test);
		adl_scene_manager->spawnActor(multi_actor, adlVec3(i * 3, 0, 0));
	}

	adlCamera* camera = ADL_NEW(adlCamera);
	camera->set_camera_type(ct_rts);
	adl_scene_manager->set_camera(camera);

	adl_window->set_mouse_visible(false);

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

	return true;
}
