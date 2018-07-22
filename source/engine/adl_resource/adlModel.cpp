#include "adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"

#include <GL/glew.h>

adlModel::adlModel()
{
	
}

adlModel::~adlModel()
{
	
}

void adlModel::add_mesh(adlMesh_shared_ptr mesh)
{
	meshes_.push_back(mesh);
}

void adlModel::print_vertices()
{
	for (unsigned int i = 0; i < meshes_.size(); i++)
	{
		meshes_[i]->print_vertices();
	}
}

void adlModel::draw()
{
	if (is_wire_frame_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	shader_->start();
	for (auto mesh : meshes_)
	{
		glBindVertexArray(mesh->get_vao_id());
		//glBindVertexArray(mesh->getVaoID());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawArrays(GL_TRIANGLES, 0, mesh->get_vertex_count());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);
	}
	shader_->stop();
}

void adlModel::set_shader(adlShader_shared_ptr shader)
{
	shader_ = shader;
	for (auto mesh : meshes_)
	{
		mesh->set_shader(shader);
	}
}

void adlModel::set_wire_frame_mode(bool is_wire_frame)
{
	is_wire_frame_ = is_wire_frame;
}

bool adlModel::get_wire_frame_mode()
{
	return is_wire_frame_;
}
