#include "adlMesh.h"

#include <stdio.h>

adlMesh::adlMesh()
	:	texture_(nullptr)
{
	glGenVertexArrays(1, &vao_);
}

adlMesh::~adlMesh()
{
	
}

void adlMesh::add_vertices(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	vertices_ = vertices;
	indices_ = indices;
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

	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<float> uvs;

	for (auto vertex : vertices_)
	{
		positions.push_back(vertex.position.x);
		positions.push_back(vertex.position.y);
		positions.push_back(vertex.position.z);

		normals.push_back(vertex.normal.x);
		normals.push_back(vertex.normal.y);
		normals.push_back(vertex.normal.z);

		uvs.push_back(vertex.uv.x);
		uvs.push_back(vertex.uv.y);
	}

	store_data_in_attribute_list(0, positions, 3, mesh_vertex_count * 3);
	store_data_in_attribute_list(1, normals, 3, mesh_vertex_count * 3);
	store_data_in_attribute_list(2, uvs, 2, mesh_vertex_count * 2);

	uint32 ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);


	glBindVertexArray(0);
}

void adlMesh::store_data_in_attribute_list(int attribute_number, const std::vector<float>& data, int32 stride, int count)
{
	uint32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribute_number, stride, GL_FLOAT, GL_FALSE, 0, 0);

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

int adlMesh::get_index_count()
{
	return indices_.size();
}

void adlMesh::set_material(adlMaterial_shared_ptr material)
{
	material_ = material;
}

adlMaterial_shared_ptr adlMesh::get_material()
{
	return material_;
}

adlVec3 adlMesh::get_bb_dimensions()
{
	adlVec3 dims;
	dims.x = std::abs(bounding_box_.bottom_left_back().x - bounding_box_.bottom_right_back().x) / 2;
	dims.y = std::abs(bounding_box_.bottom_left_back().y - bounding_box_.up_left_back().y) / 2;
	dims.z = std::abs(bounding_box_.bottom_left_back().z - bounding_box_.bottom_left_front().z) / 2;
	if (dims.x == 0.0f)
	{
		dims.x = 0.1f;
	}
	if (dims.y == 0.0f)
	{
		dims.y = 0.1f;
	}
	if (dims.z == 0.0f)
	{
		dims.z = 0.1f;
	}

	return dims;
}