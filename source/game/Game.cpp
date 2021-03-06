#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"
#include "engine/adl_entities/adlPhysics_component.h"
#include "engine/adl_entities/adlPoint_light_component.h"
#include "engine/adl_entities/adlSun_component.h"
#include "game/Test_component.h"

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
	adlPoint_light_component l;
	adlSun_component sun;
	Test_component test_c;
	adlScene_shared_ptr scene = adl_scene_manager->create_empty_scene("new_scene");
	adl_scene_manager->set_active_scene(scene);

	scene->set_cube_map(adl_rm->get_cube_map("default"));
	
	listener_ = ADL_NEW(Physics_listener);
	adl_scene_manager->add_physics_observer(listener_);

	adlCamera* scene_camera = ADL_NEW(adlCamera);
	scene_camera->set_camera_type(ct_god_mode);
	scene_camera->init();
	scene_camera->set_pitch(-50);
	scene_camera->set_position(adlVec3(0, 30, 10));

	adl_scene_manager->set_camera(scene_camera);

	adl_window->set_mouse_visible(false);

	scene->set_camera(scene_camera);

	adlTerrain_shared_ptr terrain = adl_rm->get_terrain("test_terrain");
	terrain->set_blend_map(adl_rm->get_texture("black"));
	terrain->set_texture_pack(adl_rm->get_texture_pack("default"));
	adl_scene_manager->set_terrain(terrain);

	entity = adl_scene_manager->add_entity_to_scene("test_entity");
	std::shared_ptr<adlRender_component> render_comp = std::shared_ptr(entity->get_component<adlRender_component>("adlRender_component"));
	render_comp->set_material(adl_rm->get_material("frame"));
	adl_scene_manager->set_sun(entity);
	adlEntity_shared_ptr entity1 = adl_scene_manager->add_entity_to_scene("test_entity");

	std::shared_ptr<adlTransform_component> component = std::shared_ptr(entity->get_component<adlTransform_component>("adlTransform_component"));

	adlEntity_shared_ptr monkey = adl_scene_manager->add_entity_to_scene("Monkey");


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
