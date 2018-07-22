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
		adlLogger::log_error("Could not open core resource file at %s\n", core_file_path.c_str());
	}

	return file_text;
}

adlModel_shared_ptr adlResource_manager::get_model(const std::string& model_name)
{
	if (!name_to_model_path_[model_name].empty())
	{
		const std::string model_path = name_to_model_path_[model_name];
		if (models_[model_path] == nullptr)
		{
			adlLogger::log_info("Model " + model_name + " is not loaded yet. Loading.");
			models_[model_path] = loader_.load_model(model_path);
			return models_[model_path];
		}
		else
		{
			adlLogger::log_info("Model is loaded. Returning pointer");
			return models_[model_path];
		}
	}

	adlLogger::log_error("Model" + model_name + "doesn't exist. Returning nullptr");

	return nullptr;
}

adlShader_shared_ptr adlResource_manager::get_shader(const std::string& shader_name)
{
	if (!name_to_shader_path_[shader_name].first.empty() && !name_to_shader_path_[shader_name].second.empty())
	{
		const std::pair<std::string, std::string>& shader_paths = name_to_shader_path_[shader_name];
		if (shaders_[shader_paths] == nullptr)
		{
			const std::string vertex_shader_path = name_to_shader_path_[shader_name].first;
			const std::string fragment_shader_path = name_to_shader_path_[shader_name].second;

			adlLogger::log_info("Shader " + shader_name + " is not loaded yet. Loading");
			shaders_[shader_paths] = loader_.load_shader(vertex_shader_path, fragment_shader_path);
			return shaders_[shader_paths];
		}
		else
		{
			adlLogger::log_info("Shader is loaded. Returning pointer");
			return shaders_[shader_paths];
		}
	}
}