#ifndef adl_mesh_h__
#define adl_mesh_h__

#include "engine/common.h"
#include "engine/adl_math/adlMath.h"
#include "adlResource.h"
#include "engine/adlShared_types.h"

#include <GL/glew.h>

enum Texture_type
{
	tt_specular,
	tt_diffuse
};

struct Vertex
{
	adlVec3 position;
	adlVec3 normal;
	adlVec2 uv;

	Vertex()
		: position(adlVec3::zero()), normal(adlVec3::zero()), uv(adlVec2::zero())
	{

	}

	Vertex(adlVec3 position, adlVec3 normal, adlVec2 uv) 
		: position(position), normal(normal), uv(uv)
	{
	}
};

struct Texture
{
	unsigned int texture_id;
	std::string type;
};

class adlMesh
{
public:
	adlMesh();
	virtual ~adlMesh();

	void add_vertices(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void set_shader(adlShader_shared_ptr shader);
	void print_vertices();

	uint32 get_vao_id();
	int get_vertex_count();
	int get_index_count();

private:
	void load_mesh_to_vao();
	void store_data_in_attribute_list(int attribute_number, const std::vector<float>& data, int32 stride, int count);

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	uint32 vao_, ebo_;

	adlShader_shared_ptr shader_;
};

#endif // adl_mesh_h__