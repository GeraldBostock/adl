#ifndef adl_model_h__
#define adl_model_h__

#include <vector>
#include "adl_resource/adlMesh.h"
#include "adlShared_types.h"

class adlModel
{
public:
	adlModel();
	virtual ~adlModel();

	void add_mesh(adlMesh_shared_ptr mesh);
	void print_vertices();

private:
	std::vector<adlMesh_shared_ptr> meshes_;
};

#endif // adl_model_h__