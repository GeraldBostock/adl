#ifndef adl_terrain_h__
#define adl_terrain_h__

#include "engine/adl_resource/adlMesh.h"
#include "engine/adlShared_types.h"

#include <string>
#include <vector>
#include <set>

class adlTerrain
{
public:
	adlTerrain(int width, int height, const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const std::string& name,
		const std::vector<adlVec3>& faces, const std::vector<adlVec3>& face_normals, const std::vector<float>& heightfield);
	~adlTerrain();

	adlModel_shared_ptr get_model();
	const std::string& get_name();

	void set_blend_map(adlTexture_shared_ptr texture)
	{
		blend_map_ = texture;
	}
	adlTexture_shared_ptr get_blend_map()
	{
		return blend_map_;
	}

	const Vertex& get_vertex_at_index(int iVertex, int jVertex);
	int get_width();
	int get_height();

	void edit_vertex(int i, int j);
	void edit_vertices(const std::set<std::pair<int, int>>& vertex_indices, const std::vector<Vertex>& vertex_values);

	const std::vector<Vertex>& get_vertices();
	const std::vector<adlVec3>& get_face_normals()
	{
		return face_normals_;
	}
	const std::vector<adlVec3>& get_faces()
	{
		return faces_;
	}

	const std::vector<float>& get_heightfield()
	{
		return heightfield_;
	}

private:

	void calculate_normal(int i, int j);

	int width_;
	int height_;
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<adlVec3> faces_;
	std::vector<adlVec3> face_normals_;
	std::vector<float> heightfield_;

	adlModel_shared_ptr terrain_model_;
	adlTexture_shared_ptr blend_map_;
	std::string name_;
};

#endif // adl_terrain_h__
