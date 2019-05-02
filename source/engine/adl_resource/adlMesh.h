#ifndef adl_mesh_h__
#define adl_mesh_h__

#include "engine/common.h"
#include "engine/adl_math/adlMath.h"
#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlMaterial.h"
#include "engine/adl_resource/adlBounding_box.h"


#include <vector>
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

	std::string to_string()
	{
		std::string struct_string = "";
		struct_string += "x: " + std::to_string(position.x) + ", y: " + std::to_string(position.y) + ", z: " + std::to_string(position.z);
		return struct_string;
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
	void set_material(adlMaterial_shared_ptr material);
	void print_vertices();

	uint32 get_vao_id();
	int get_vertex_count();
	int get_index_count();
	adlMaterial_shared_ptr get_material();

	void set_texture(adlTexture_shared_ptr texture)
	{
		texture_ = texture;
	}

	adlTexture_shared_ptr get_texture()
	{
		return texture_;
	}

	void set_bounding_box(adlBounding_box bb)
	{
		bounding_box_ = bb;
	}

	adlBounding_box get_bounding_box()
	{
		return bounding_box_;
	}

	adlVec3 get_bb_dimensions();

private:
	void load_mesh_to_vao();
	void store_data_in_attribute_list(int attribute_number, const std::vector<float>& data, int32 stride, int count);

	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;
	adlTexture_shared_ptr texture_;

	uint32 vao_, ebo_;

	adlShader_shared_ptr shader_;
	adlMaterial_shared_ptr material_;
	adlBounding_box bounding_box_;
};

#endif // adl_mesh_h__
