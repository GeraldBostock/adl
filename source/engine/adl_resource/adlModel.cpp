#include "adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include "engine/adl_renderer/adlDebug_renderer.h"
#include "engine/adl_resource/adlTexture.h"

#include <iostream>

#include <GL/glew.h>

adlModel::adlModel(const std::string& name)
{
	name_ = name;
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

void adlModel::draw(adlShader_shared_ptr shader, adlMat4 transformation_matrix)
{
	for (auto mesh : meshes_)
	{
		adlMaterial_shared_ptr mtl = mesh->get_material();
		shader->load_material(mtl);

		/*if (mesh->get_texture() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->get_texture()->get_id());
			shader->load_texture();
		}*/

		glBindVertexArray(mesh->get_vao_id());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

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
}

void adlModel::set_material(adlMaterial_shared_ptr material)
{
	for (auto mesh : meshes_)
	{
		mesh->set_material(material);
		mesh->set_texture(nullptr);
	}
}

std::string adlModel::get_name()
{
	return name_;
}

const std::vector<adlMesh_shared_ptr>& adlModel::get_all_meshes()
{
	return meshes_;
}

void adlModel::set_texture(adlTexture_shared_ptr texture)
{
	for (auto mesh : meshes_)
	{
		mesh->set_texture(texture);
	}
}

adlTexture_shared_ptr adlModel::get_texture()
{
	return texture_;
}

void adlModel::set_bounding_box(adlBounding_box bb)
{
	bb_ = bb;
}

adlBounding_box adlModel::get_bounding_box()
{
	return bb_;
}