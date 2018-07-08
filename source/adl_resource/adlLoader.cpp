#include "adlLoader.h"

#include "adlMesh.h"
#include "adl_debug\adlLogger.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>

adlLoader::adlLoader()
{

}

adlLoader::~adlLoader()
{

}

adlMesh_shared_ptr adlLoader::load_mesh(const std::string& mesh_path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(mesh_path,
		aiProcess_Triangulate |
		aiProcess_FlipUVs
		);

	if (!scene)
	{
		adlLogger::log_error(importer.GetErrorString());
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	aiMesh* mesh = scene->mMeshes[0];
	aiVector3D* mesh_vertices = mesh->mVertices;
	aiVector3D* mesh_normals = mesh->mNormals;
	aiVector3D** mesh_uvs = mesh->mTextureCoords;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		adlVec3 position(mesh_vertices[i].x, mesh_vertices[i].y, mesh_vertices[i].z);
		adlVec3 normal(mesh_normals[i].x, mesh_normals[i].y, mesh_normals[i].z);
		adlVec2 uv;

		if (mesh_uvs[0])
		{
			uv.x = mesh_uvs[0][i].x;
			uv.y = mesh_uvs[0][i].y;
		}
		else
		{
			uv = adlVec2(0.0f, 0.0f);
		}

		vertices.push_back(Vertex(position, normal, uv));
	}
	adlLogger::log_error(mesh_path + " contains more than one mesh. This function is used for loading a single mesh");

	return nullptr;
}