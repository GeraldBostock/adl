#ifndef adl_physics_h__
#define adl_physics_h__

#include "adlPhysics_world.h"

class adlPhysics
{
public:

	static adlPhysics& get()
	{
		static adlPhysics instance;
		return instance;
	}

	adlPhysics_world* create_new_world();

private:
	adlPhysics();
};

#endif //adl_physics_h__