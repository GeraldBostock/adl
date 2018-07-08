#include "adlMesh.h"

adlMesh::adlMesh()
{
	
}

adlMesh::~adlMesh()
{
	
}

void adlMesh::load()
{
	adl_assert(!is_loaded_);
	is_loaded_ = true;
}

void adlMesh::unload()
{
	adl_assert(is_loaded_);
	is_loaded_ = false;
}

void adlMesh::setup_mesh()
{

}