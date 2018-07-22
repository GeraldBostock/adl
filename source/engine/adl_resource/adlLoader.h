#ifndef adl_loader_h__
#define adl_loader_h__

#include "engine/adlShared_types.h"
#include "adlMesh.h"

class adlMesh;
struct aiNode;
struct aiScene;
struct aiMesh;

class adlLoader
{
public:
	adlLoader();
	virtual ~adlLoader();

	adlModel_shared_ptr load_model(const std::string& mesh_path);
private:
	void process_ai_node(aiNode* node, const aiScene* scene, adlModel_shared_ptr model);
	adlMesh_shared_ptr process_mesh(aiMesh *mesh, const aiScene *scene);
};

#endif // adl_loader_h__