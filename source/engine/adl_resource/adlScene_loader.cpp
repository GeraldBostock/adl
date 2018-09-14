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
	std::vector<adlActor_shared_ptr> actors_array;
	std::vector<adlPoint_light_shared_ptr> point_lights_array;
	std::vector<adlEntity_shared_ptr> entities_array;

	std::string scene_text = get_whole_file_string(scene_path);
	rapidjson::Document document;

	document.Parse(scene_text.c_str());
	adl_assert(document.IsObject());


	const rapidjson::Value& sun_object = document["sun"];
	adl_assert(sun_object.IsObject());
	adlSun_shared_ptr sun = load_sun(sun_object);

	std::cout << "a" << std::endl;

	const rapidjson::Value& actors = document["actors"];
	for (rapidjson::Value::ConstValueIterator itr = actors.Begin(); itr != actors.End(); ++itr)
	{
		const rapidjson::Value& actor_object = *itr;
		adlActor_shared_ptr actor = load_actor(actor_object);
		actor->deserialize(actor_object);
		actors_array.push_back(actor);
	}

	const rapidjson::Value& lights = document["point_lights"];
	for (rapidjson::Value::ConstValueIterator itr = lights.Begin(); itr != lights.End(); ++itr)
	{
		const rapidjson::Value& light_object = *itr;
		adlPoint_light_shared_ptr point_light = load_point_light(light_object);
		point_lights_array.push_back(point_light);
	}

	adlCamera* camera = ADL_NEW(adlCamera);
	adlScene_shared_ptr scene = MAKE_SHARED(adlScene, "Dicks", entities_array, actors_array, point_lights_array);
	scene->set_sun(sun);
	scene->set_camera(camera);

	return scene;
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

adlActor_shared_ptr adlScene_loader::load_actor(const rapidjson::Value& object)
{
	adlEntity_factory* factory = &adlEntity_factory::get();
	adlResource_manager* adl_rm = &adlResource_manager::get();

	std::string type_name = object["type_name"].GetString();
	adlActor* actor = (adlActor*)factory->construct_actor(type_name);
	adlActor_shared_ptr actor_shared(actor);

	std::string actor_name = object["name"].GetString();
	adlVec3 position = load_vec3(object, "position");
	adlVec3 rotation = load_vec3(object, "rotation");
	adlVec3 scale = load_vec3(object, "scale");
	
	std::string model_name = object["model_name"].GetString();
	std::string material_name = object["material_name"].GetString();

	actor_shared->set_name(actor_name);
	actor_shared->set_position(position);
	actor_shared->set_rotation(rotation);
	actor_shared->set_scale(scale);

	actor_shared->set_model(adl_rm->get_model(model_name));
	
	if (material_name != "")
	{
		actor_shared->set_material(adl_rm->get_material(material_name));
	}

	return actor_shared;
}

adlSun_shared_ptr adlScene_loader::load_sun(const rapidjson::Value& object)
{
	std::string sun_name = object["name"].GetString();

	adlVec3 position = load_vec3(object, "position");
	adlVec3 rotation = load_vec3(object, "rotation");
	adlVec3 scale = load_vec3(object, "scale");
	adlVec3 ambient = load_vec3(object, "ambient");
	adlVec3 diffuse = load_vec3(object, "diffuse");
	adlVec3 specular = load_vec3(object, "specular");

	adlSun_shared_ptr sun = MAKE_SHARED(adlSun);
	sun->set_name(sun_name);
	sun->set_position(position);
	sun->set_rotation(rotation);
	sun->set_scale(scale);
	sun->set_ambient(ambient);
	sun->set_diffuse(diffuse);
	sun->set_specular(specular);

	return sun;
}

adlPoint_light_shared_ptr adlScene_loader::load_point_light(const rapidjson::Value& object)
{
	adlEntity_factory* factory = &adlEntity_factory::get();
	std::string type_name = object["type_name"].GetString();

	adlPoint_light* light = (adlPoint_light*)factory->construct_light(type_name);

	adlVec3 position = load_vec3(object, "position");
	adlVec3 rotation = load_vec3(object, "rotation");
	adlVec3 scale = load_vec3(object, "scale");
	adlVec3 ambient = load_vec3(object, "ambient");
	adlVec3 diffuse = load_vec3(object, "diffuse");
	adlVec3 specular = load_vec3(object, "specular");
	float constant = object["constant"].GetFloat();
	float linear = object["linear"].GetFloat();
	float quadratic = object["quadratic"].GetFloat();

	adlPoint_light_shared_ptr light_shared(light);
	light_shared->set_position(position);
	light_shared->set_rotation(rotation);
	light_shared->set_scale(scale);
	light_shared->set_ambient(ambient);
	light_shared->set_diffuse(diffuse);
	light_shared->set_specular(specular);
	light_shared->set_constant(constant);
	light_shared->set_linear(linear);
	light_shared->set_quadratic(quadratic);

	return light_shared;
}
