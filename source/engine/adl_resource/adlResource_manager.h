#ifndef adl_resource_manager_h__
#define adl_resource_manager_h__

#include <string>
#include <map>

#include <document.h>

#include "engine/adl_debug/adlLogger.h"
#include "adlLoader.h"

class adlResource_manager
{
public:
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

private:
	adlResource_manager();
	std::string get_core_file_string();
	std::string get_materials_string();

	adlResource_manager(adlResource_manager const&) = delete;
	void operator=(adlResource_manager const&)		= delete;

	void initialize_models(const rapidjson::Value& models);
	void initialize_shaders(const rapidjson::Value& shaders);
	void initialize_fonts(const rapidjson::Value& fonts);
	void initialize_materials(const rapidjson::Value& materials);
	void initialize_textures(const rapidjson::Value& textures);

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

	adlLoader loader_;

	adlModel_shared_ptr model;
};

#endif // adl_resource_manager_h__

