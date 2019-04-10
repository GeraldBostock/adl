#ifndef adl_resource_manager_h__
#define adl_resource_manager_h__

#include <string>
#include <map>

#include <document.h>

#include "engine/adl_debug/adlLogger.h"
#include "adlScene_saver.h"
#include "adlLoader.h"

enum Resources
{
	MODEL,
	SHADER,
	FONT,
	MATERIAL,
	TEXTURE,
	SCENE,
	TERRAIN,
	CUBE_MAP,
	ENTITY,
	RESOURCE_TYPE_COUNT
};

class adlResource_manager
{
public:

	friend class adlResource_manager_editor;

	static adlResource_manager& get()
	{
		static adlResource_manager instance;
		return instance;
	}

	adlModel_shared_ptr get_model(const std::string& model_name);
	adlModel_shared_ptr getModel(const std::string& model_name);

	adlShader_shared_ptr get_shader(const std::string& shader_name);
	adlShader_shared_ptr getShader(const std::string& shader_name);

	adlFont_shared_ptr get_font(const std::string& font_name);
	adlFont_shared_ptr getFont(const std::string& font_name);

	adlMaterial_shared_ptr get_material(const std::string& material_name);
	adlMaterial_shared_ptr getMaterial(const std::string& material_name);

	adlScene_shared_ptr get_scene(const std::string& name);

	adlTerrain_shared_ptr get_terrain(const std::string& name);

	adlTexture_shared_ptr get_texture(const std::string& name);

	adlCube_map_shared_ptr get_cube_map(const std::string& name);

	void reload_resource(const std::string& resource_path, Resources type);

	std::string get_entity_json(const std::string& entity_name);

	void add_new_scene(const std::string& scene_name, adlScene_shared_ptr scene);

	std::string serialize_scene(adlScene_shared_ptr scene);

	std::vector<std::string> get_all_scene_names();
	const std::vector<std::string>& get_all_entity_names();

private:
	adlResource_manager();
	std::string get_core_file_string();
	std::string get_materials_string();
	std::string get_whole_file_string(const std::string& file_path);

	adlResource_manager(adlResource_manager const&) = delete;
	void operator=(adlResource_manager const&)		= delete;

	void initialize_models(const rapidjson::Value& models);
	void initialize_shaders(const rapidjson::Value& shaders);
	void initialize_fonts(const rapidjson::Value& fonts);
	void initialize_materials(const rapidjson::Value& materials);
	void initialize_textures(const rapidjson::Value& textures);
	void initialize_scenes(const rapidjson::Value& scenes);
	void initialize_terrains(const rapidjson::Value& terrains);
	void initialize_cube_maps(const rapidjson::Value& cube_maps);
	void initialize_entities(const rapidjson::Value& entities);

	void reload_model(const std::string& model_name);
	void reload_entity(const std::string& entity_name);

	const std::string core_file_path = "res/core.json";
	const std::string materials_file_path = "res/materials.json";
	
	std::map<std::string, std::string> name_to_model_path_;
	std::map<std::string, adlModel_shared_ptr> models_;

	std::map<std::string, std::pair<std::string, std::string>> name_to_shader_path_;
	std::map<std::pair<std::string, std::string>, adlShader_shared_ptr> shaders_;

	std::map<std::string, std::string> name_to_font_path_;
	std::map<std::string, adlFont_shared_ptr> fonts_;

	std::map<std::string, adlMaterial_shared_ptr> materials_;

	std::map<std::string, std::pair<std::string, std::string>> name_to_texture_path_;
	std::map<std::string, adlTexture_shared_ptr> textures_;

	std::map<std::string, std::string> name_to_scene_path_;
	std::map<std::string, adlScene_shared_ptr> scenes_;

	std::map<std::string, std::string> name_to_terrain_path_;
	std::map<std::string, adlTerrain_shared_ptr> terrains_;

	std::map<std::string, std::vector<std::string>> name_to_cubemap_path_;
	std::map<std::string, adlCube_map_shared_ptr> cube_maps_;

	std::map<std::string, std::string> name_to_entity_path_;
	std::map<std::string, std::string> entity_json_string_;

	std::vector<std::string> entity_names_;

	adlLoader loader_;
	adlScene_saver scene_saver_;

	adlModel_shared_ptr model;
};

#endif // adl_resource_manager_h__

