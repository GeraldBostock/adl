#ifndef adl_model_h__
#define adl_model_h__

#include <vector>

#include "engine/adl_resource/adlMesh.h"
#include "engine/adlShared_types.h"

class adlModel
{
public:
	adlModel(const std::string& name);
	virtual ~adlModel();

	void add_mesh(adlMesh_shared_ptr mesh);
	void add_mesh(adlMesh mesh);
	void print_vertices();
	void set_material(adlMaterial_shared_ptr material);
	std::string get_name();

	void set_bounding_box(adlBounding_box bb);
	adlBounding_box get_bounding_box();

	void set_texture(adlTexture_shared_ptr texture);
	adlTexture_shared_ptr get_texture();

	void draw(adlShader_shared_ptr shader, adlMat4 transformation_matrix);

	const std::vector<adlMesh_shared_ptr>& get_all_meshes();

private:
	std::vector<adlMesh_shared_ptr> meshes_;
	std::vector<adlMesh> value_meshes_;
	std::string name_ = "";
	adlTexture_shared_ptr texture_;

	adlBounding_box bb_;
};

#endif // adl_model_h__