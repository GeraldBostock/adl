#include "adlMesh.h"

#include <stdio.h>

adlMesh::adlMesh()
{
}

adlMesh::~adlMesh()
{
	
}

void adlMesh::add_vertices(std::vector<Vertex>& vertices)
{
	vertices_ = vertices;
}

void adlMesh::print_vertices()
{
	for (int i = 0; i < vertices_.size(); i++)
	{
		printf("x: %f, y: %f, z: %f\n", vertices_[i].position.vec[0], vertices_[i].position.vec[1], vertices_[i].position.vec[2]);
	}
}