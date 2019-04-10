#ifndef adl_loader_h__
#define adl_loader_h__

#include "engine/adlShared_types.h"
#include "adlMesh.h"
#include "adlScene_loader.h"

#include <stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>

class adlMesh;
struct aiNode;
struct aiScene;
struct aiMesh;

class adlLoader
{
public:
	adlLoader();
	virtual ~adlLoader();

	adlModel_shared_ptr load_model(const std::string& mesh_path, const std::string& model_name);
	adlShader_shared_ptr load_shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
	adlFont_shared_ptr load_font(const std::string& font_path);
	adlTexture_shared_ptr load_texture(const std::pair<std::string, std::string>& texture_paths);
	adlScene_shared_ptr load_scene(const std::string& scene_path);
	adlTerrain_shared_ptr load_terrain(const std::string& terrain_path, const std::string& terrain_name);
	adlCube_map_shared_ptr load_cube_map(const std::vector<std::string>& faces);

private:
	void process_ai_node(aiNode* node, const aiScene* scene, adlModel_shared_ptr model);
	adlMesh_shared_ptr process_mesh(aiMesh *mesh, const aiScene* scene);

	void load_texture_from_file(unsigned int texture_id, const std::string& file_path, adlTexture_shared_ptr texture);

	void generate_bounding_box(adlVec2 min_max_x, adlVec2 min_max_y, adlVec2 min_max_z);

	adlScene_loader scene_loader_;
};

#endif // adl_loader_h__