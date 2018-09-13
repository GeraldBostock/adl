#ifndef adl_scene_loader_h__
#define adl_scene_loader_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlScene.h"
#include "engine/adl_entities/adlEntity_factory.h"

#include <document.h>

class adlScene_loader
{
public:
	adlScene_loader();
	~adlScene_loader();

	adlScene_shared_ptr load_scene(const std::string& scene_path);
private:
	std::string get_whole_file_string(const std::string& file_path);

	adlVec3 load_vec3(const rapidjson::Value& object, std::string array_name);

	adlActor_shared_ptr load_actor(const rapidjson::Value& object);
	adlSun_shared_ptr load_sun(const rapidjson::Value& object);
	adlPoint_light_shared_ptr load_point_light(const rapidjson::Value& object);
};

#endif // adl_scene_loader_h__