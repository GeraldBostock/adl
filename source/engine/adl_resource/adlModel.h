#ifndef adl_model_h__
#define adl_model_h__

#include <vector>
#include "engine/adl_resource/adlMesh.h"
#include "engine/adlShared_types.h"

class adlModel
{
public:
	adlModel();
	virtual ~adlModel();

	void add_mesh(adlMesh_shared_ptr mesh);
	void print_vertices();

	void set_shader(adlShader_shared_ptr shader);
	void set_frame(adlMatrix_frame& frame);
	adlMatrix_frame get_frame();
	void draw();

private:
	std::vector<adlMesh_shared_ptr> meshes_;
	adlShader_shared_ptr shader_;

	adlMatrix_frame frame_;
};

#endif // adl_model_h__