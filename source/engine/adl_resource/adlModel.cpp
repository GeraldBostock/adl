#include "adlModel.h"

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
