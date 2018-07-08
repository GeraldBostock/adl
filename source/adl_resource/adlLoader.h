#ifndef adl_loader_h__
#define adl_loader_h__

#include "adlMesh.h"

class adlMesh;

typedef std::shared_ptr<adlMesh> adlMesh_shared_ptr;

class adlLoader
{
public:
	adlLoader();
	virtual ~adlLoader();

	adlMesh_shared_ptr load_mesh(const std::string& mesh_path);
private:

};

#endif // adl_loader_h__