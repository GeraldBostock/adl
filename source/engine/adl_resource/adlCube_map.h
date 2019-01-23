#ifndef adl_cube_map_h__
#define adl_cube_map_h__

#include "../common.h"

#include <GL/glew.h>

class adlCube_map
{
public:
	adlCube_map();
	~adlCube_map();

	uint32 get_id()
	{
		return texture_id_;
	}

private:
	uint32 texture_id_;
};

#endif //adl_cube_map_h__