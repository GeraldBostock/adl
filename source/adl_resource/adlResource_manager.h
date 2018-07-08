#ifndef adl_resource_manager_h__
#define adl_resource_manager_h__

#include <string>
#include <map>

#include "rapidjson/document.h"
#include "adl_debug\adlLogger.h"
#include "adlResource.h"
#include "adlLoader.h"

class adlResource_manager
{
public:
	static adlResource_manager& get()
	{
		static adlResource_manager instance;
		return instance;
	}

	adlMesh_shared_ptr get_mesh(const std::string& mesh_name);

private:
	adlResource_manager();
	std::string get_core_file_string();

	adlResource_manager(adlResource_manager const&) = delete;
	void operator=(adlResource_manager const&)		= delete;

	const std::string core_file_path = "../res/core.json";

	std::map<std::string, adlMesh_shared_ptr> meshes;
};

#endif // adl_resource_manager_h__

