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
	adlModel_shared_ptr mountain_model = adl_rm->get_model("mountain");
	adlModel_shared_ptr teapot_model = adl_rm->get_model("teapot");

	shader = adl_rm->get_shader("basic_shader");
	model->set_shader(shader);
	box->set_shader(shader);
	mountain_model->set_shader(shader);
	teapot_model->set_shader(shader);

	adlModel_shared_ptr cube_model = adl_rm->get_model("cube");
	cube_model->set_shader(shader);

	adlMatrix_frame frame = adlMatrix_frame::identity();

	light_ = ADL_NEW(adlLight, cube_model, adlColor::WHITE);
	frame.scale = adlVec3(0.1f);
	frame.o = adlVec3(0, 5, 0);
	light_->set_frame(frame);
	adl_renderer->set_light(light_);

	bison_entity_.set_model(model);
	box1_.set_model(box);
	box2_.set_model(box);
	mount_.set_model(mountain_model);
	teapot_entity_.set_model(teapot_model);

	box1_.set_frame(frame);
	box2_.set_frame(frame);
	frame.rot = adlVec3(adlMath::deg_to_rad(90), 0, 0);
	bison_entity_.set_frame(frame);

	frame.rot = adlVec3(adlMath::deg_to_rad(90), 0, 0);
	frame.o = adlVec3(0, -10.0f, 0);
	mount_.set_frame(frame);
	teapot_entity_.set_frame(frame);

	for (int i = 0; i < 20; i++)
	{
		adlEntity entity;
		entity.set_model(cube_model);
		frame.o = adlVec3((float)i * 2 - 10, 0, 0);
		frame.scale = adlVec3(0.5f);
		entity.set_frame(frame);
		boxes_.push_back(entity);
	}

	adlMat4 projection = projection.create_projection_matrix(window_->get_width(), window_->get_height(), adlMath::deg_to_rad(40), 0.1f, 1000.0f);;
	adl_renderer->set_projection(projection);
	
	camera->set_camera_type(ct_rts_camera);

	timer_.start();

	return true;
}

bool Game::update(int64 dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	adlMatrix_frame frame = adlMatrix_frame::identity();
	frame.o = adlVec3(model_x, -0.5f, -1.5f);
	frame.rot = adlVec3(0, 0, 0);
	frame.scale = adlVec3(0.5f, 0.5f, 0.5f);
	bison_entity_.set_frame(frame);

	frame = adlMatrix_frame::identity();
	frame.o = adlVec3(0, -0.5f, -10.0f);
	frame.rot = adlVec3(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds()) / 8, 0, 0);
	frame.scale = adlVec3(1.1f, 1.1f, 1.1f);
	box1_.set_frame(frame);


	for (int i = 0; i < 20; i++)
	{
		adlMatrix_frame box_frame = boxes_[i].get_frame();
		box_frame.rot = adlVec3(0, adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds()) / 8, 0);
		boxes_[i].set_frame(box_frame);
		adl_renderer->render(boxes_[i], adlColor::RED);
	}

	frame.rot = adlVec3(0.0f);
	frame.o = adlVec3(0, -10.0f, 0);
	mount_.set_frame(frame);

	frame.o = adlVec3(0, 0, -20.0f);
	frame.rot = adlVec3(adlMath::deg_to_rad(-90), 0, 0);
	frame.scale = adlVec3(0.05f);
	teapot_entity_.set_frame(frame);

	adl_renderer->render(box1_, adlColor::BLUE);
	adl_renderer->render(bison_entity_, adlColor::BLUE);
	adl_renderer->render(teapot_entity_, adlColor::WHITE);
	adl_renderer->render(mount_, adlColor::GREEN);

	frame.o = adlVec3(std::sin(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds() / 8)) * 10, 5, 0);
	light_->set_frame(frame);
	adl_renderer->render(light_);


	return true;
}