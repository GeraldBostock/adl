#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlSun.h"
#include "engine/adl_entities/adlEntity_factory.h"

#include "game/Human.h"
#include "game/Interfaces/IMovementBehaviour.h"


Game::Game()
{

}

Game::~Game()
{

}

adlActor_shared_ptr human = MAKE_SHARED(Human);


bool Game::init()
{
	adlScene_shared_ptr scene = adl_scene_manager->create_empty_scene("new_scene");
	adl_scene_manager->set_active_scene(scene);

	//adlActor_shared_ptr actor = MAKE_SHARED(Test_actor);
	//actor->set_name("Big_Ass_Cube_#1");
	//adl_scene_manager->addToScene(actor);
	Material_new_test new_test;
	Material_test test;
	Test_actor test_a;

	//adlActor_shared_ptr landscape = MAKE_SHARED(Test_actor);
	//adl_scene_manager->addToScene(landscape);
	//landscape->set_position(adlVec3(0, -15, 0));
	//landscape->setModel(adl_rm->getModel("Landscape"));
	//landscape->set_name("Landscape");

	adl_scene_manager->addToScene(human);
	human->setModel(adl_rm->getModel("Human"));


	//adlActor_shared_ptr material_actor = MAKE_SHARED(Material_test);
	//adl_scene_manager->addToScene(material_actor);


	//adlActor_shared_ptr axisArrow = MAKE_SHARED(adlActor);
	//adl_scene_manager->addToScene(axisArrow);
	//axisArrow->setPosition(adlVec3(5.0f, 0.0f, 8.0f));
	////axisArrow->setRotation(adlVec3(0.0f, 0.0f, 0.0f));
	//axisArrow->setScale(adlVec3(1.0f));
	//axisArrow->setModel(adl_rm->getModel("AxisArrow"));
	//axisArrow->set_name("AxisArrowBlend");

	//adlActor_shared_ptr axisArrowFBX = MAKE_SHARED(adlActor);
	//adl_scene_manager->addToScene(axisArrowFBX);
	//axisArrowFBX->setPosition(adlVec3(10.0f, 0.0f, 8.0f));
	////axisArrowFBX->setRotation(adlVec3(0.0f, 0.0f, 0.0f));
	//axisArrowFBX->setScale(adlVec3(1.0f));
	//axisArrowFBX->setModel(adl_rm->getModel("AxisArrowFBX"));
	//axisArrowFBX->set_name("AxisArrowFBX");

	//adlActor_shared_ptr axisArrowOBJ = MAKE_SHARED(adlActor);
	//adl_scene_manager->addToScene(axisArrowOBJ);
	//axisArrowOBJ->setPosition(adlVec3(15.0f, 0.0f, 8.0f));
	//axisArrowOBJ->setRotation(adlVec3(0.0f, 0.0f, 0.0f));
	//axisArrowOBJ->setScale(adlVec3(1.0f));
	//axisArrowOBJ->setModel(adl_rm->getModel("AxisArrowOBJ"));
	//axisArrowOBJ->set_name("AxisArrowOBJ");

	//adlActor_shared_ptr wuson = MAKE_SHARED(Material_new_test);
	//adl_scene_manager->addToScene(wuson);

	adlSun_shared_ptr sun = MAKE_SHARED(adlSun);
	sun->set_position(adlVec3(0, 20, 20));
	adl_scene_manager->setSun(sun);

	adlPoint_light_shared_ptr point_light = MAKE_SHARED(adlPoint_light);
	adl_scene_manager->addPointLightToScene(point_light);
	point_light->set_position(adlVec3(0, 10, 20));
	point_light->set_name("Light_#1");

	//adlPoint_light_shared_ptr second_light = MAKE_SHARED(adlPoint_light);
	//adl_scene_manager->addPointLightToScene(second_light);
	//second_light->set_position(adlVec3(0, 10, 20));
	//second_light->set_name("Light_#2");

	//for (int i = 0; i < 20; i++)
	//{
	//	adlActor_shared_ptr multi_actor = MAKE_SHARED(Material_test);
	//	adl_scene_manager->spawnActor(multi_actor, adlVec3(i * 3, 0, 0));
	//}

	adlCamera* camera = ADL_NEW(adlCamera);
	camera->set_camera_type(ct_rts);
	camera->init();

	adl_scene_manager->set_camera(camera);

	adl_window->set_mouse_visible(false);

	/*adlEntity_factory* factory = &adlEntity_factory::get();
	adlActor* new_actor = (adlActor*)factory->construct_actor("Test_actor");
	if (new_actor != nullptr)
	{
		adlActor_shared_ptr my_ptr(new_actor);
		adl_scene_manager->addToScene(my_ptr);
		my_ptr->set_position(adlVec3(0, 10, 0));
		my_ptr->set_name("Big_Ass_Cube_#2");
	}*/

	scene->set_sun(sun);
	scene->set_camera(camera);
	scene->spawn_point_light(point_light);
	//scene->spawn_point_light(second_light);
	//scene->spawn_actor(landscape);
	scene->spawn_actor(human);
	
	human->set_position(adlVec3(0, 3, -4));
	human->setRotation(adlVec3(-90, 0, 0));


	std::shared_ptr<Human> h =
		std::dynamic_pointer_cast<Human> (human);
	
	WalkMovement walker;
	RunMovement runner;

	h->SetMovementBehaviour(&walker);
	h->MoveTo();

	h->SetMovementBehaviour(&runner);
	h->MoveTo();

	//adlScene_shared_ptr default_scene = adl_rm->get_scene("default_scene");
	//adl_scene_manager->set_active_scene(default_scene);

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

	adlScene_shared_ptr scene = adl_scene_manager->get_active_scene();
	const std::vector<adlActor_shared_ptr>& actors = scene->get_all_actors();

	for (auto actor : actors)
	{
		adlVec3 position = actor->get_position();
		debug_renderer->render_sphere(position, adlColor(210, 52, 30), 0.1f);
	}

	const std::vector<adlPoint_light_shared_ptr> lights = scene->get_all_point_lights();
	
	for (auto light : lights)
	{
		adlVec3 position = light->get_position();
		debug_renderer->render_box(position, 0.01f, adlColor(210, 52, 30));
	}

	adlSun_shared_ptr sun = scene->get_sun();
	adlActor_shared_ptr actor = actors[0];
	debug_renderer->render_line3D(sun->get_position(), actor->get_position(), 2.0f, adlColor::YELLOW);

	return true;
}
