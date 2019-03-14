#include "adlScene_saver.h"

#include "engine/adl_resource/adlScene.h"
#include "engine/adl_entities/adlEntities.h"
#include "engine/adl_debug/adlLogger.h"

adlScene_saver::adlScene_saver()
{
}


adlScene_saver::~adlScene_saver()
{
}

std::string adlScene_saver::get_serialized_scene(adlScene_shared_ptr scene)
{
	//const std::vector<adlEntity_shared_ptr>& entities = scene->get_all_entities();

	std::string serialized_scene = "{";

	return serialized_scene;
}

std::string adlScene_saver::serialize_vec3(const std::string& name, adlVec3 vector)
{
	std::string serialized_vector = "";

	std::string x_string = std::to_string(vector.x);
	std::string y_string = std::to_string(vector.y);
	std::string z_string = std::to_string(vector.z);

	serialized_vector += "\"" + name + "\":[" + x_string + "," + y_string + "," + z_string + "]";

	return serialized_vector;
}
