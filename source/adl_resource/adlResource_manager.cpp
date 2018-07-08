#include "adlResource_manager.h"
#include "adl_debug\adlAssert.h"

#include <fstream>
#include <sstream>
#include <iostream>

adlResource_manager::adlResource_manager()
{
	std::string core_file_string = get_core_file_string();

	rapidjson::Document document;
	document.Parse(core_file_string.c_str());

	adl_assert(document.IsObject());

	const rapidjson::Value& mesh_paths = document["meshes"];
	const rapidjson::Value& texture_paths = document["textures"];

	for (rapidjson::SizeType i = 0; i < mesh_paths.Size(); i++)
	{
		adlMesh_shared_ptr mesh = std::make_shared<adlMesh>();
		mesh->set_file_path(mesh_paths[i].GetString());
		meshes[mesh_paths[i].GetString()] = mesh;
	}

	for (rapidjson::SizeType i = 0; i < mesh_paths.Size(); i++)
		printf("a[%d] = %s\n", i, mesh_paths[i].GetString());

	for (rapidjson::SizeType i = 0; i < texture_paths.Size(); i++)
		printf("a[%d] = %s\n", i, texture_paths[i].GetString());
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

adlMesh_shared_ptr adlResource_manager::get_mesh(const std::string& mesh_name)
{
	if (meshes.count(mesh_name) == 0)
	{
		adlLogger::log_error("Mesh " + mesh_name + " does not exist in the resource database");
	}
	else
	{
		if (meshes[mesh_name]->is_loaded())
		{
			adlLogger::log_info("Mesh " + mesh_name + " is already loaded.\nReturning reference");
			return meshes[mesh_name];
		}
		else
		{
			adlLogger::log_info("Mesh " + mesh_name + " exists but it hasn't been loaded yet.\nLoading");
			meshes[mesh_name]->load();
			return meshes[mesh_name];
		}
	}

	return nullptr;
}