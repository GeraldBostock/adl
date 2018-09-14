#ifndef adl_scene_saver_h__
#define adl_scene_saver_h__

#include "engine/adlShared_types.h"

#include <string>

class adlScene_saver
{
public:
	adlScene_saver();
	~adlScene_saver();

	void save_scene(adlScene_shared_ptr scene);
private:
	std::string serialize_actor(adlActor_shared_ptr actor);
};

#endif // adl_scene_saver_h__