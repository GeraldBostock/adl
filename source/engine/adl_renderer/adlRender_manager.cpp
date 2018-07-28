#include "adlRender_manager.h"

#include "engine/adl_resource/adlModel.h"
#include <iostream>

#include <GL/glew.h>

adlRender_manager::adlRender_manager()
{
	is_wire_frame_mode_ = false;
}

adlRender_manager::~adlRender_manager()
{

}

void adlRender_manager::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.79f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void adlRender_manager::render_mesh(adlModel_shared_ptr model)
{
	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	model->draw();
}

void adlRender_manager::set_wire_frame_mode()
{
	is_wire_frame_mode_ = !is_wire_frame_mode_;

}