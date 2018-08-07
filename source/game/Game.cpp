#include "Game.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adlInput.h"
#include "engine/adlMemory.h"
#include "engine/adlWindow.h"

#include <iostream>

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
	box2 = adl_rm->get_model("box");

	shader = adl_rm->get_shader("basic_shader");
	model->set_shader(shader);
	box->set_shader(shader);
	box2->set_shader(shader);

	adlMatrix_frame frame = adlMatrix_frame::identity();
	model->set_frame(frame);
	box->set_frame(frame);
	box2->set_frame(frame);
	timer_.start();

	adlMat4 projection = projection.create_projection_matrix(window_->get_width(), window_->get_height(), adlMath::deg_to_rad(70), 0.1f, 1000.0f);;
	adl_renderer->set_projection(projection);

	return true;
}

bool Game::update(int64 dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key(adl_key_w))
	{
		model_z -= 0.2f;
	}
	if (adl_input->get_key(adl_key_s))
	{
		model_z += 0.2f;
	}
	if (adl_input->get_key(adl_key_a))
	{
		model_x -= 0.2f;
	}
	if (adl_input->get_key(adl_key_d))
	{
		model_x += 0.2f;
	}

	adlMatrix_frame frame = adlMatrix_frame::identity();
	frame.o = adlVec3(model_x, -0.5f, model_z);
	frame.rot = adlVec3(0, adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds()) / 8, 0);
	frame.scale = adlVec3(0.5f, 0.5f, 0.5f);
	model->set_frame(frame);

	frame = adlMatrix_frame::identity();
	frame.o = adlVec3(0, -0.5f, -10.0f);
	frame.rot = adlVec3(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds()) / 8, 0, 0);
	frame.scale = adlVec3(1.1f, 1.1f, 1.1f);
	box->set_frame(frame);
	adl_renderer->render_mesh(box);

	adl_renderer->render_mesh(model);

	return true;
}