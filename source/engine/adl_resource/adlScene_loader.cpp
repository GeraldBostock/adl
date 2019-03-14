#include "adlScene_loader.h"

#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_entities/adlEntities.h"
#include "engine/adl_resource/adlResource_manager.h"

#include <fstream>
#include <sstream>

adlScene_loader::adlScene_loader()
{
}


adlScene_loader::~adlScene_loader()
{
}

adlScene_shared_ptr adlScene_loader::load_scene(const std::string& scene_path)
{
	std::vector<adlEntity_shared_ptr> entities_array;

	std::string scene_text = get_whole_file_string(scene_path);
	rapidjson::Document document;

	document.Parse(scene_text.c_str());
	adl_assert(document.IsObject());

	const rapidjson::Value& sun_object = document["sun"];
	adl_assert(sun_object.IsObject());

	const rapidjson::Value& actors = document["actors"];
	for (rapidjson::Value::ConstValueIterator itr = actors.Begin(); itr != actors.End(); ++itr)
	{
		const rapidjson::Value& actor_object = *itr;
	}

	const rapidjson::Value& lights = document["point_lights"];
	for (rapidjson::Value::ConstValueIterator itr = lights.Begin(); itr != lights.End(); ++itr)
	{
		const rapidjson::Value& light_object = *itr;
	}

	adlCamera* camera = ADL_NEW(adlCamera);

	return nullptr;
}

std::string adlScene_loader::get_whole_file_string(const std::string& file_path)
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
		adl_logger->log_error("Could not open file at " + file_path);
	}

	return file_text;
}

adlVec3 adlScene_loader::load_vec3(const rapidjson::Value& object, std::string array_name)
{
	const rapidjson::Value& vec_array = object[array_name.c_str()];

	rapidjson::Value::ConstValueIterator itr = vec_array.Begin();

	const rapidjson::Value& x = *itr;
	const rapidjson::Value& y = *++itr;
	const rapidjson::Value& z = *++itr;

	adlVec3 vec3(x.GetFloat(), y.GetFloat(), z.GetFloat());

	return vec3;
}
