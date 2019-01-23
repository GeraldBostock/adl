#ifndef adl_terrain_h__
#define adl_terrain_h__

#include "engine/adl_resource/adlMesh.h"
#include "engine/adlShared_types.h"

#include <string>
#include <vector>

class adlTerrain
{
public:
	adlTerrain(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const std::string& name,
		const std::vector<adlVec3>& faces, const std::vector<adlVec3>& face_normals);
	~adlTerrain();

	adlModel_shared_ptr get_model();
	const std::string& get_name();

	const std::vector<Vertex>& get_vertices();
	const std::vector<adlVec3>& get_face_normals()
	{
		return face_normals_;
	}
	const std::vector<adlVec3>& get_faces()
	{
		return faces_;
	}

private:
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<adlVec3> faces_;
	std::vector<adlVec3> face_normals_;

	adlModel_shared_ptr terrain_model_;
	std::string name_;
};

#endif // adl_terrain_h__
