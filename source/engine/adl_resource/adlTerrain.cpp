#include "adlTerrain.h"

#include "engine/adl_resource/adlModel.h"

adlTerrain::adlTerrain(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const std::string& name,
	const std::vector<adlVec3>& faces, const std::vector<adlVec3>& face_normals, const std::vector<float>& heightfield)
	:	vertices_(vertices),
		indices_(indices),
		name_(name),
		faces_(faces),
		face_normals_(face_normals),
		heightfield_(heightfield)
{
	terrain_model_ = MAKE_SHARED(adlModel, "terrain");
	
	adlMesh mesh;
	mesh.add_vertices(vertices_, indices_);
	terrain_model_->add_mesh(mesh);
}

adlTerrain::~adlTerrain()
{

}

adlModel_shared_ptr adlTerrain::get_model()
{
	return terrain_model_;
}

const std::string& adlTerrain::get_name()
{
	return name_;
}

const std::vector<Vertex>& adlTerrain::get_vertices()
{
	return vertices_;
}