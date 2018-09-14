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
	const std::vector<adlEntity_shared_ptr>& entities = scene->get_all_entities();
	const std::vector<adlActor_shared_ptr>& actors = scene->get_all_actors();
	const std::vector<adlPoint_light_shared_ptr>& lights = scene->get_all_point_lights();
	const adlSun_shared_ptr sun = scene->get_sun();

	std::string serialized_scene = "{";

	std::string sun_serialized = serialize_sun(sun);
	serialized_scene += sun_serialized + ",\"actors\":[";

	for (unsigned int i = 0; i < actors.size(); i++)
	{
		adlActor_shared_ptr actor = actors[i];
		std::string serialized_actor = serialize_actor(actor);
		serialized_scene += serialized_actor;
		if (i != actors.size() - 1)
		{
			serialized_scene += ",";
		}
	}

	serialized_scene += "],\"point_lights\":[";

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		adlPoint_light_shared_ptr light = lights[i];
		std::string serialized_light = serialize_point_light(light);
		serialized_scene += serialized_light;
		if (i != lights.size() - 1)
		{
			serialized_scene += ",";
		}
	}

	serialized_scene += "]}";

	return serialized_scene;
}

std::string adlScene_saver::serialize_actor(adlActor_shared_ptr actor)
{
	std::string serialized_string = "{";

	std::string type_name = actor->get_type_name();
	std::string actor_name = actor->get_name();
	std::string model_name = "";
	if (actor->get_model() != nullptr)
	{
		model_name = actor->get_model()->get_name();
	}

	std::string material_name = "";
	if (actor->get_material() != nullptr)
	{
		material_name = actor->get_material()->get_name();
	}

	serialized_string += "\"type_name\":\"" + type_name + "\",";
	serialized_string += "\"name\":\"" + actor_name + "\",";

	adlVec3 position = actor->get_position();
	adlVec3 rotation = actor->get_rotation();
	adlVec3 scale = actor->get_scale();

	std::string position_string = serialize_vec3("position", position);
	std::string rotation_string = serialize_vec3("rotation", rotation);
	std::string scale_string = serialize_vec3("scale", scale);

	serialized_string += position_string + "," + rotation_string + "," + scale_string + ",";
	serialized_string += "\"model_name\":\"" + model_name + "\",";
	serialized_string += "\"material_name\":\"" + material_name + "\"}";

	return serialized_string;
}

std::string adlScene_saver::serialize_sun(adlSun_shared_ptr sun)
{
	std::string serialized_string = "\"sun\":{";

	//std::string type_name = sun->get_type_name();
	std::string name = sun->get_name();
	serialized_string += "\"name\":\"" + name + "\",";

	adlVec3 position = sun->get_position();
	adlVec3 rotation = sun->get_rotation();
	adlVec3 scale = sun->get_scale();
	adlVec3 ambient = sun->get_ambient();
	adlVec3 diffuse = sun->get_diffuse();
	adlVec3 specular = sun->get_specular();

	std::string position_string = serialize_vec3("position", position);
	std::string rotation_string = serialize_vec3("rotation", rotation);
	std::string scale_string = serialize_vec3("scale", scale);
	std::string ambient_string = serialize_vec3("ambient", ambient);
	std::string diffuse_string = serialize_vec3("diffuse", diffuse);
	std::string specular_string = serialize_vec3("specular", specular);

	serialized_string += position_string + "," + rotation_string + "," + scale_string + "," + ambient_string + "," + diffuse_string + "," + specular_string + "}";

	return serialized_string;
}

std::string adlScene_saver::serialize_point_light(adlPoint_light_shared_ptr light)
{
	std::string serialized_string = "";

	std::string type_name = light->get_type_name();
	std::string light_name = light->get_name();
	
	adlVec3 position = light->get_position();
	adlVec3 rotation = light->get_rotation();
	adlVec3 scale = light->get_scale();
	adlVec3 ambient = light->get_ambient();
	adlVec3 diffuse = light->get_diffuse();
	adlVec3 specular = light->get_specular();

	float constant = light->get_constant();
	float linear = light->get_linear();
	float quadratic = light->get_quadratic();

	std::string position_string = serialize_vec3("position", position);
	std::string rotation_string = serialize_vec3("rotation", rotation);
	std::string scale_string = serialize_vec3("scale", scale);
	std::string ambient_string = serialize_vec3("ambient", ambient);
	std::string diffuse_string = serialize_vec3("diffuse", diffuse);
	std::string specular_string = serialize_vec3("specular", specular);

	std::string constant_string = std::to_string(constant);
	std::string linear_string = std::to_string(linear);
	std::string quadratic_string = std::to_string(quadratic);

	serialized_string += "{\"type_name\":\"" + type_name + "\",";
	serialized_string += "\"name\":\"" + light_name + "\",";
	serialized_string += position_string + "," + rotation_string + "," + scale_string + ",";
	serialized_string += ambient_string + "," + diffuse_string + "," + specular_string + ",";
	serialized_string += "\"constant\":" + constant_string + ",";
	serialized_string += "\"linear\":" + linear_string + ",";
	serialized_string += "\"quadratic\":" + quadratic_string + "}";

	return serialized_string;
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
