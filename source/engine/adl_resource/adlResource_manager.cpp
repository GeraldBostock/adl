#include "adlResource_manager.h"
#include "engine/adl_debug/adlAssert.h"

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
	const rapidjson::Value& shader_objects = document["shaders"];
	const rapidjson::Value& font_objects = document["fonts"];

	adl_assert(mesh_objects.IsArray());
	adl_assert(shader_objects.IsArray());

	for (rapidjson::Value::ConstValueIterator itr = mesh_objects.Begin(); itr != mesh_objects.End(); ++itr)
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

	for (rapidjson::Value::ConstValueIterator itr = shader_objects.Begin(); itr != shader_objects.End(); ++itr)
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

	for (rapidjson::Value::ConstValueIterator itr = font_objects.Begin(); itr != font_objects.End(); itr++)
	{
		const rapidjson::Value& font_object = *itr;
		adl_assert(font_object.IsObject());
		
		const std::string name = font_object["name"].GetString();
		const std::string path = font_object["path"].GetString();

		name_to_font_path_[name] = path;
		fonts_[path] = nullptr;
	}
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

adlModel_shared_ptr adlResource_manager::get_model(const std::string& model_name)
{
	adlLogger* adl_logger = &adlLogger::get();
	if (!name_to_model_path_[model_name].empty())
	{
		const std::string model_path = name_to_model_path_[model_name];
		if (models_[model_path] == nullptr)
		{
			adl_logger->log_info("Model " + model_name + " is not loaded yet. Loading.");
			models_[model_path] = loader_.load_model(model_path);
			return models_[model_path];
		}
		else
		{
			return models_[model_path];
		}
	}

	adl_logger->log_error("Model" + model_name + "doesn't exist. Returning nullptr");

	return nullptr;
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