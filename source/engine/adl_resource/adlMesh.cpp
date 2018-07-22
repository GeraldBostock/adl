#include "adlMesh.h"

#include <stdio.h>

adlMesh::adlMesh()
{
	glGenVertexArrays(1, &vao_);
}

adlMesh::~adlMesh()
{
	
}

void adlMesh::add_vertices(std::vector<Vertex>& vertices)
{
	vertices_ = vertices;
	load_mesh_to_vao();
}

void adlMesh::print_vertices()
{
	for (unsigned int i = 0; i < vertices_.size(); i++)
	{
		printf("x: %f, y: %f, z: %f\n", vertices_[i].position.vec[0], vertices_[i].position.vec[1], vertices_[i].position.vec[2]);
	}
}

void adlMesh::load_mesh_to_vao()
{
	glBindVertexArray(vao_);

	int mesh_vertex_count = vertices_.size();

	std::vector<adlVec3> positions;
	positions.resize(mesh_vertex_count);

	std::vector<adlVec3> normals;
	normals.resize(mesh_vertex_count);

	std::vector<adlVec2> uvs;
	uvs.resize(mesh_vertex_count);

	for (int i = 0; i < mesh_vertex_count; i++)
	{
		positions[i] = vertices_[i].position;
		normals[i] = vertices_[i].normal;
		uvs[i] = vertices_[i].uv;
	}

	store_data_in_attribute_list(0, positions, mesh_vertex_count);
	store_data_in_attribute_list(1, normals, mesh_vertex_count);
	store_uv_data_in_attribute_list(2, uvs, mesh_vertex_count);

	glBindVertexArray(0);
}

void adlMesh::store_data_in_attribute_list(int attribute_number, const std::vector<adlVec3>& data, int count)
{
	uint32 vbo_;
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(data[0]), &data[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attribute_number, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void adlMesh::store_uv_data_in_attribute_list(int attribute_number, const std::vector<adlVec2>& data, int count)
{
	uint32 vbo_;
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(data[0]), &data[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attribute_number, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void adlMesh::set_shader(adlShader_shared_ptr shader)
{
	shader_ = shader;
}

uint32 adlMesh::get_vao_id()
{
	return vao_;
}

int adlMesh::get_vertex_count()
{
	return vertices_.size();
}
