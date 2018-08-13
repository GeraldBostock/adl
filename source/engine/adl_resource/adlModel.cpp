#include "adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"

#include <iostream>

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

void adlModel::add_mesh(adlMesh mesh)
{
	value_meshes_.push_back(mesh);
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
	shader_->start();
	for (auto mesh : meshes_)
	{
		glBindVertexArray(mesh->get_vao_id());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//glDrawArrays(GL_TRIANGLES, 0, mesh->get_vertex_count());
		glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	for (auto mesh : value_meshes_)
	{
		glBindVertexArray(mesh.get_vao_id());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);
	}
	shader_->stop();
}

adlShader_shared_ptr adlModel::get_shader()
{
	return shader_;
}

void adlModel::set_shader(adlShader_shared_ptr shader)
{
	shader_ = shader;
	for (auto mesh : meshes_)
	{
		mesh->set_shader(shader);
	}
}

void adlModel::set_frame(adlMatrix_frame& frame)
{
	frame_.o = frame.o;
	frame_.rot = frame.rot;
	frame_.scale = frame.scale;
}

adlMatrix_frame adlModel::get_frame()
{
	return frame_;
}
