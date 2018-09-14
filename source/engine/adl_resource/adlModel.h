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

	void draw(adlShader_shared_ptr shader);

private:
	std::vector<adlMesh_shared_ptr> meshes_;
	std::vector<adlMesh> value_meshes_;
	std::string name_ = "";
};

#endif // adl_model_h__