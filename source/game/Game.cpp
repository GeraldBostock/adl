#include "Game.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adlInput.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	model = adl_rm->get_model("wuson");
	box = adl_rm->get_model("box");
	shader = adl_rm->get_shader("basic_shader");
	model->set_shader(shader);
	box->set_shader(shader);
	model->set_wire_frame_mode(true);
	return true;
}

bool Game::update(double dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key(adl_key_left_alt) && adl_input->get_key_up(adl_key_w))
	{
		model->set_wire_frame_mode(!model->get_wire_frame_mode());
	}
	model->draw();
	box->draw();

	return true;
}