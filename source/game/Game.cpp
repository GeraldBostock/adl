#include "Game.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_renderer/adlRender_manager.h"
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
	return true;
}

bool Game::update(int64 dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	adl_renderer->render_mesh(model);
	adl_renderer->render_mesh(box);

	return true;
}