#include "adlRender_manager.h"

#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include <iostream>

#include <GL/glew.h>

adlRender_manager::adlRender_manager()
{
	is_wire_frame_mode_ = false;
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

adlRender_manager::~adlRender_manager()
{

}

void adlRender_manager::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void adlRender_manager::render(adlEntity entity, adlColor color)
{
	adlModel_shared_ptr model = entity.get_model();
	adlMat4 view_matrix = camera_->get_view_matrix();
	adlShader_shared_ptr shader = model->get_shader();
	shader->start();
	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * entity.get_frame().get_transformation_matrix();
	shader->load_mvp(mvp_matrix);
	shader->load_object_color(color.to_vec3());
	shader->load_light_color(light_->get_color().to_vec3());
	shader->load_light_position(light_->get_frame().transform.o);
	shader->load_model_matrix(entity.get_frame().get_transformation_matrix());

	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	model->draw();
	shader->stop();
}

void adlRender_manager::render(adlLight* light)
{
	adlModel_shared_ptr model = light->get_model();
	adlMat4 view_matrix = camera_->get_view_matrix();
	adlShader_shared_ptr shader = light->get_shader();
	shader->start();
	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * light->get_frame().get_transformation_matrix();
	shader->load_mvp(mvp_matrix);
	shader->load_light_color(light_->get_color().to_vec3());

	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	model->draw();
	shader->stop();
}

void adlRender_manager::set_wire_frame_mode()
{
	is_wire_frame_mode_ = !is_wire_frame_mode_;
}

void adlRender_manager::set_projection(adlMat4 projection_matrix)
{
	projection_matrix_ = projection_matrix;
}

void adlRender_manager::set_camera(adlCamera* camera)
{
	camera_ = camera;
}

void adlRender_manager::set_light(adlLight* light)
{
	light_ = light;
}
