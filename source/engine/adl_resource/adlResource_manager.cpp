#include "adlResource_manager.h"
#include "engine/adl_debug/adlAssert.h"
#include "engine/adl_resource/adlMaterial.h"

#include "engine/adl_entities/adlSun.h"

#include <fstream>
#include <sstream>
#include <iostream>

adlResource_manager::adlResource_manager()
{
	std::string core_file_string = get_core_file_string();

	rapidjson::Document document;
	document.Parse(core_file_string.c_str());

	adl_assert(document.IsObject());

	const rapidjson::Value& mesh_objects = document["models"];
	adl_assert(mesh_objects.IsArray());
	initialize_models(mesh_objects);

	const rapidjson::Value& shader_objects = document["shaders"];
	adl_assert(shader_objects.IsArray());
	initialize_shaders(shader_objects);

	const rapidjson::Value& font_objects = document["fonts"];
	adl_assert(font_objects.IsArray());
	initialize_fonts(font_objects);

	std::string materials_file_string = get_materials_string();

	rapidjson::Document materials_document;
	materials_document.Parse(materials_file_string.c_str());
	adl_assert(materials_document.IsObject());
	const rapidjson::Value& material_objects = materials_document["materials"];
	adl_assert(material_objects.IsArray());
	initialize_materials(material_objects);

	const rapidjson::Value& texture_objects = document["textures"];
	adl_assert(texture_objects.IsArray());
	initialize_textures(texture_objects);

	const rapidjson::Value& scene_objects = document["scenes"];
	adl_assert(scene_objects.IsArray());
	initialize_scenes(scene_objects);

	const rapidjson::Value& terrain_objects = document["terrains"];
	adl_assert(terrain_objects.IsArray());
	initialize_terrains(terrain_objects);

	const rapidjson::Value& cube_map_objects = document["cube_maps"];
	adl_assert(cube_map_objects.IsArray());
	initialize_cube_maps(cube_map_objects);

	const rapidjson::Value& entity_objects = document["entities"];
	adl_assert(entity_objects.IsArray());
	initialize_entities(entity_objects);
}

std::string adlResource_manager::get_core_file_string()
{
	std::ifstream file;
	file.open(core_file_path);

	std::string file_text;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			file_text.append(line + "\n");
		}
	}
	else
	{
		adlLogger* adl_logger = &adlLogger::get();
		adl_logger->log_error("Could not open core resource file at %s\n", core_file_path.c_str());
	}

	return file_text;
}

std::string adlResource_manager::get_materials_string()
{
	std::ifstream file;
	file.open(materials_file_path);

	std::string file_text;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			file_text.append(line + "\n");
		}
	}
	else
	{
		adlLogger* adl_logger = &adlLogger::get();
		adl_logger->log_error("Could not open core resource file at %s\n", materials_file_path.c_str());
	}

	return file_text;
}

std::string adlResource_manager::get_whole_file_string(const std::string& file_path)
{
	std::ifstream file;
	file.open(file_path);

	std::string file_text;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			file_text.append(line + "\n");
		}
	}
	else
	{
		adlLogger* adl_logger = &adlLogger::get();
		adl_logger->log_error("Could not open file at %s\n", file_path.c_str());
	}

	return file_text;
}

adlModel_shared_ptr adlResource_manager::get_model(const std::string& model_name)
{
	adlLogger* adl_logger = &adlLogger::get();
	if (!name_to_model_path_[model_name].empty())
	{
		const std::string model_path = name_to_model_path_[model_name];
		if (models_[model_path] == nullptr)
		{
			adl_logger->log_info("Model " + model_name + " is not loaded yet. Loading.");
			models_[model_path] = loader_.load_model(model_path, model_name);
			return models_[model_path];
		}
		else
		{
			return models_[model_path];
		}
	}

	adl_logger->log_error("Model " + model_name + " doesn't exist. Returning nullptr");

	return nullptr;
}

adlModel_shared_ptr adlResource_manager::getModel(const std::string& model_name)
{
	return get_model(model_name);
}

adlShader_shared_ptr adlResource_manager::get_shader(const std::string& shader_name)
{
	adlLogger* adl_logger = &adlLogger::get();
	if (!name_to_shader_path_[shader_name].first.empty() && !name_to_shader_path_[shader_name].second.empty())
	{
		const std::pair<std::string, std::string>& shader_paths = name_to_shader_path_[shader_name];
		if (shaders_[shader_paths] == nullptr)
		{
			const std::string vertex_shader_path = name_to_shader_path_[shader_name].first;
			const std::string fragment_shader_path = name_to_shader_path_[shader_name].second;

			adl_logger->log_info("Shader " + shader_name + " is not loaded yet. Loading");
			shaders_[shader_paths] = loader_.load_shader(vertex_shader_path, fragment_shader_path);
			return shaders_[shader_paths];
		}
		else
		{
			return shaders_[shader_paths];
		}
	}

	return nullptr;
}

adlShader_shared_ptr adlResource_manager::getShader(const std::string& shader_name)
{
	return get_shader(shader_name);
}

adlFont_shared_ptr adlResource_manager::get_font(const std::string& font_name)
{
	adlLogger* adl_logger = &adlLogger::get();
	if (!name_to_font_path_[font_name].empty())
	{
		const std::string& path = name_to_font_path_[font_name];
		if (fonts_[path] == nullptr)
		{
			adl_logger->log_info("Font " + font_name + " is not loaded yet. Loading");
			fonts_[path] = loader_.load_font(path);
			return fonts_[path];
		}
		else
		{
			return fonts_[path];
		}
	}
	return nullptr;
}

adlFont_shared_ptr adlResource_manager::getFont(const std::string& font_name)
{
	return get_font(font_name);
}

adlMaterial_shared_ptr adlResource_manager::get_material(const std::string& material_name)
{
	adlLogger* adl_logger = &adlLogger::get();
	adlMaterial_shared_ptr material = materials_[material_name];
	if (material == nullptr)
	{
		adl_logger->log_error("Material " + material_name + " does not exist.");
	}
	else if(material->get_shader() == nullptr || material->get_texture() == nullptr)
	{
		//adl_logger->log_info("Loading material '" + material_name + "'.");
		if (material->get_shader() == nullptr)
		{
			material->set_shader(get_shader(material->get_shader_name()));
		}

		if (material->get_texture() == nullptr && material->get_texture_name() != "")
		{
			std::string texture_name = material->get_texture_name();
			if (textures_[texture_name] == nullptr)
			{
				textures_[texture_name] = loader_.load_texture(name_to_texture_path_[texture_name]);
			}
			material->set_texture(textures_[texture_name]);
		}
		return material;
	}
	else if (material->get_shader() != nullptr)
	{
		return material;
	}

	return nullptr;
}

adlMaterial_shared_ptr adlResource_manager::getMaterial(const std::string& material_name)
{
	return get_material(material_name);
}

adlScene_shared_ptr adlResource_manager::get_scene(const std::string& name)
{
	if (scenes_[name] != nullptr)
	{
		return scenes_[name];
	}

	adlLogger* adl_logger = &adlLogger::get();
	if (name_to_scene_path_[name].empty())
	{
		adl_logger->log_error("Scene " + name + " could not be found.");
		return nullptr;
	}
	else
	{
		if (scenes_[name] == nullptr)
		{
			adl_logger->log_info("Scene " + name + " is not loaded yet. Loading scene.");

			adlScene_shared_ptr scene = loader_.load_scene(name_to_scene_path_[name]);

			scenes_[name] = scene;
			return scenes_[name];
		}
		else
		{
			return scenes_[name];
		}
	}
}

adlTerrain_shared_ptr adlResource_manager::get_terrain(const std::string& name)
{
	adlLogger* adl_logger = &adlLogger::get();

	if (terrains_[name] != nullptr)
	{
		return terrains_[name];
	}

	if (name_to_terrain_path_[name].empty())
	{
		adl_logger->log_error("Terrain " + name + " could not be found.");
		return nullptr;
	}
	else
	{
		if (terrains_[name] == nullptr)
		{
			adl_logger->log_info("Terrain " + name + " is not loaded yet. Loading terrain.");
			adlTerrain_shared_ptr terrain = loader_.load_terrain(name_to_terrain_path_[name], name);
			
			terrains_[name] = terrain;
			return terrain;
		}
	}

	return nullptr;
}

adlCube_map_shared_ptr adlResource_manager::get_cube_map(const std::string& name)
{
	adlLogger* adl_logger = &adlLogger::get();

	if (cube_maps_[name] != nullptr)
	{
		return cube_maps_[name];
	}

	if (name_to_cubemap_path_[name].empty())
	{
		adl_logger->log_error("Cube map " + name + " could not be found.");
		return nullptr;
	}
	else
	{
		if (cube_maps_[name] == nullptr)
		{
			adl_logger->log_info("Loading cube map " + name);
			adlCube_map_shared_ptr cube_map = loader_.load_cube_map(name_to_cubemap_path_[name]);

			cube_maps_[name] = cube_map;
			return cube_map;
		}
	}

	return nullptr;
}

std::string adlResource_manager::get_entity_json(const std::string& entity_name)
{
	adlLogger* adl_logger = &adlLogger::get();
	if (entity_json_string_[entity_name] != "")
	{
		return entity_json_string_[entity_name];
	}
	
	if (name_to_entity_path_[entity_name].empty())
	{
		adl_logger->log_error("Entity " + entity_name + "could not be found");
		return "";
	}
	else
	{
		if (entity_json_string_[entity_name] == "")
		{
			std::string file_string = get_whole_file_string(name_to_entity_path_[entity_name]);
			//std::cout << file_string << std::endl;
			entity_json_string_[entity_name] = file_string;

			return file_string;
		}
	}

	return "";
}

void adlResource_manager::initialize_models(const rapidjson::Value& models)
{
	for (rapidjson::Value::ConstValueIterator itr = models.Begin(); itr != models.End(); ++itr)
	{
		const rapidjson::Value& mesh_object = *itr;
		adl_assert(mesh_object.IsObject());

		rapidjson::Value::ConstMemberIterator itr2 = mesh_object.MemberBegin();
		const std::string name = itr2->value.GetString();
		itr2++;
		const std::string path = itr2->value.GetString();
		name_to_model_path_[name] = path;
		models_[path] = nullptr;
	}
}

void adlResource_manager::initialize_shaders(const rapidjson::Value& shaders)
{
	for (rapidjson::Value::ConstValueIterator itr = shaders.Begin(); itr != shaders.End(); ++itr)
	{
		const rapidjson::Value& shader_object = *itr;
		adl_assert(shader_object.IsObject());

		rapidjson::Value::ConstMemberIterator itr2 = shader_object.MemberBegin();
		const std::string name = itr2->value.GetString();
		itr2++;
		const std::string vertex_shader_path = itr2->value.GetString();
		itr2++;
		const std::string fragment_shader_path = itr2->value.GetString();

		name_to_shader_path_[name].first = vertex_shader_path;
		name_to_shader_path_[name].second = fragment_shader_path;
		shaders_[name_to_shader_path_[name]] = nullptr;
	}
}

void adlResource_manager::initialize_fonts(const rapidjson::Value& fonts)
{
	for (rapidjson::Value::ConstValueIterator itr = fonts.Begin(); itr != fonts.End(); itr++)
	{
		const rapidjson::Value& font_object = *itr;
		adl_assert(font_object.IsObject());

		const std::string name = font_object["name"].GetString();
		const std::string path = font_object["path"].GetString();

		name_to_font_path_[name] = path;
		fonts_[path] = nullptr;
	}
}

void adlResource_manager::initialize_materials(const rapidjson::Value& materials)
{
	for (rapidjson::Value::ConstValueIterator itr = materials.Begin(); itr != materials.End(); ++itr)
	{
		adlMaterial_shared_ptr material = std::make_shared<adlMaterial>();

		const rapidjson::Value& material_object = *itr;

		const std::string material_name = material_object["name"].GetString();
		const rapidjson::Value& ambient_array = material_object["ambient"];
		const rapidjson::Value& diffuse_array = material_object["diffuse"];
		const rapidjson::Value& specular_array = material_object["specular"];

		rapidjson::Value::ConstValueIterator itr2 = ambient_array.Begin();

		const rapidjson::Value& ambient_x = *itr2;
		const rapidjson::Value& ambient_y = *++itr2;
		const rapidjson::Value& ambient_z = *++itr2;
		adlVec3 ambient_vec(ambient_x.GetFloat(), ambient_y.GetFloat(), ambient_z.GetFloat());

		itr2 = diffuse_array.Begin();
		const rapidjson::Value& diffuse_x = *itr2;
		const rapidjson::Value& diffuse_y = *++itr2;
		const rapidjson::Value& diffuse_z = *++itr2;
		adlVec3 diffuse_vec(diffuse_x.GetFloat(), diffuse_y.GetFloat(), diffuse_z.GetFloat());

		itr2 = specular_array.Begin();
		const rapidjson::Value& specular_x = *itr2;
		const rapidjson::Value& specular_y = *++itr2;
		const rapidjson::Value& specular_z = *++itr2;
		adlVec3 specular_vec(specular_x.GetFloat(), specular_y.GetFloat(), specular_z.GetFloat());

		const rapidjson::Value& shine = material_object["shine"];
		float shininess = shine.GetFloat();

		material->set_material(ambient_vec, diffuse_vec, specular_vec, shininess);

		std::string shader_name = material_object["shader"].GetString();
		std::string texture_name = material_object["texture"].GetString();
		material->set_names(shader_name, texture_name);

		material->set_name(material_name);

		materials_[material_name] = material;
	}
}

void adlResource_manager::initialize_textures(const rapidjson::Value& textures)
{
	for (rapidjson::Value::ConstValueIterator itr = textures.Begin(); itr != textures.End(); ++itr)
	{
		const rapidjson::Value& texture_object = *itr;
		adl_assert(texture_object.IsObject());

		std::pair<std::string, std::string> texture_paths;
		texture_paths.first = texture_object["path"].GetString();
		texture_paths.second = texture_object["specular_map_path"].GetString();

		name_to_texture_path_[texture_object["name"].GetString()] = texture_paths;
		textures_[texture_object["name"].GetString()] = nullptr;
	}
}

void adlResource_manager::initialize_scenes(const rapidjson::Value& scenes)
{
	for (rapidjson::Value::ConstValueIterator itr = scenes.Begin(); itr != scenes.End(); ++itr)
	{
		const rapidjson::Value& scene_object = *itr;
		adl_assert(scene_object.IsObject());

		std::string scene_name = scene_object["name"].GetString();
		name_to_scene_path_[scene_name] = scene_object["path"].GetString();
		scenes_[scene_name] = nullptr;
	}
}

void adlResource_manager::initialize_terrains(const rapidjson::Value& terrains)
{
	for (rapidjson::Value::ConstValueIterator itr = terrains.Begin(); itr != terrains.End(); ++itr)
	{
		const rapidjson::Value& terrain_object = *itr;
		adl_assert(terrain_object.IsObject());

		std::string terrain_name = terrain_object["name"].GetString();
		std::string height_map_path = terrain_object["height_map"].GetString();

		name_to_terrain_path_[terrain_name] = height_map_path;
		terrains_[terrain_name] = nullptr;
	}
}

void adlResource_manager::initialize_cube_maps(const rapidjson::Value& cube_maps)
{
	for (rapidjson::Value::ConstValueIterator itr = cube_maps.Begin(); itr != cube_maps.End(); ++itr)
	{
		const rapidjson::Value& cube_map_object = *itr;
		adl_assert(cube_map_object.IsObject());
		
		const std::string prefix = "res/skyboxes/";

		std::string cube_map_name = cube_map_object["name"].GetString();

		std::string right = prefix + cube_map_object["right"].GetString();
		std::string left = prefix + cube_map_object["left"].GetString();

		std::string top = prefix + cube_map_object["top"].GetString();
		std::string bottom = prefix + cube_map_object["bottom"].GetString();

		std::string back = prefix + cube_map_object["back"].GetString();
		std::string front = prefix + cube_map_object["front"].GetString();

		std::vector<std::string> faces;
		faces.push_back(right);
		faces.push_back(left);

		faces.push_back(top);
		faces.push_back(bottom);

		faces.push_back(back);
		faces.push_back(front);

		name_to_cubemap_path_[cube_map_name] = faces;
		cube_maps_[cube_map_name] = nullptr;
	}
}

void adlResource_manager::initialize_entities(const rapidjson::Value& entities)
{
	for (rapidjson::Value::ConstValueIterator it = entities.Begin(); it != entities.End(); ++it)
	{
		const rapidjson::Value& entity_object = *it;
		adl_assert(entity_object.IsObject());

		std::string entity_name = entity_object["name"].GetString();
		std::string entity_path = entity_object["path"].GetString();

		name_to_entity_path_[entity_name] = entity_path;
		entity_json_string_[entity_name] = "";
	}
}

void adlResource_manager::add_new_scene(const std::string& scene_name, adlScene_shared_ptr scene)
{
	scenes_[scene_name] = scene;
}

std::string adlResource_manager::serialize_scene(adlScene_shared_ptr scene)
{
	return scene_saver_.get_serialized_scene(scene);
}

std::vector<std::string> adlResource_manager::get_all_scene_names()
{
	std::vector<std::string> scene_names;
	for (std::map<std::string, adlScene_shared_ptr>::iterator it = scenes_.begin(); it != scenes_.end(); ++it)
	{
		scene_names.push_back(it->first);
	}

	return scene_names;
}