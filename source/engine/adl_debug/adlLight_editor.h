#ifndef adl_light_editor_h__
#define adl_light_editor_h__

#include "engine/adlShared_types.h"

#include <vector>

class adlLight_editor
{
public:
	adlLight_editor();
	~adlLight_editor();

	void update(adlSun_shared_ptr sun, std::vector<adlPoint_light_shared_ptr>& point_lights);
private:
	bool window_open_;
};

#endif // adl_light_editor_h__