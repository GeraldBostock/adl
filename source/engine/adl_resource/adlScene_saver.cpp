#include "adlScene_saver.h"

#include "engine/adl_resource/adlScene.h"
#include "engine/adl_entities/adlEntities.h"

adlScene_saver::adlScene_saver()
{
}


adlScene_saver::~adlScene_saver()
{
}

void adlScene_saver::save_scene(adlScene_shared_ptr scene)
{
	const std::vector<adlEntity_shared_ptr>& entities = scene->get_all_entities();
	const std::vector<adlActor_shared_ptr>& actors = scene->get_all_actors();
	const std::vector<adlPoint_light_shared_ptr>& lights = scene->get_all_point_lights();
	const adlSun_shared_ptr sun = scene->get_sun();
}

std::string adlScene_saver::serialize_actor(adlActor_shared_ptr actor)
{
	std::string serialized_string = "";

	std::string type_name = actor->get_type_name();
	std::string model_name;

	return "";
}
