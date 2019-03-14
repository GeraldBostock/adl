#ifndef adl_scene_saver_h__
#define adl_scene_saver_h__

#include "engine/adlShared_types.h"
#include "engine/adl_math/adlVector.h"

#include <string>

class adlScene_saver
{
public:
	adlScene_saver();
	~adlScene_saver();

	std::string get_serialized_scene(adlScene_shared_ptr scene);
private:
	/*std::string serialize_actor(adlActor_shared_ptr actor);
	std::string serialize_sun(adlSun_shared_ptr sun);
	std::string serialize_point_light(adlPoint_light_shared_ptr light);*/

	std::string serialize_vec3(const std::string& name, adlVec3 vector);
};

#endif // adl_scene_saver_h__