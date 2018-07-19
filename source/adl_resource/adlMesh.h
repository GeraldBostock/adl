#ifndef adl_mesh_h__
#define adl_mesh_h__

#include "adl_math/adlMath.h"
#include "adlResource.h"

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

	void add_vertices(std::vector<Vertex>& vertices);
	void print_vertices();

private:
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	unsigned int VAO_, VBO_, EBO_;
};

#endif // adl_mesh_h__