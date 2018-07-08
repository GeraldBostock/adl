#ifndef adl_mesh_h__
#define adl_mesh_h__

#include <memory>

#include "adl_math\adlMath.h"
#include "adlResource.h"

enum Texture_type
{
	tt_specular,
	tt_diffuse
};

struct Vertex
{
	adlVec3 position_;
	adlVec3 normal_;
	adlVec2 uv_;

	Vertex(adlVec3 position, adlVec3 normal, adlVec2 uv) 
		: position_(position), normal_(normal), uv_(uv)
	{
	}
};

struct Texture
{
	unsigned int texture_id;
	std::string type;
};

class adlMesh : public adlResource
{
public:
	adlMesh();
	virtual ~adlMesh();
	
	void load() override;
	void unload() override;

private:
	void setup_mesh();
	
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	unsigned int VAO_, VBO_, EBO_;
};

#endif // adl_mesh_h__