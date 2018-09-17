#ifndef adl_bounding_box_h__
#define adl_bounding_box_h__

#include "engine/adl_math/adlVector.h"

class adlBounding_box
{
public:
	adlBounding_box(adlVec2 min_max_x, adlVec2 min_max_y, adlVec2 min_max_z);
	adlBounding_box() {};
	~adlBounding_box();

	adlVec3 up_left_back();
	adlVec3 up_left_front();

	adlVec3 up_right_back();
	adlVec3 up_right_front();

	adlVec3 bottom_left_back();
	adlVec3 bottom_left_front();

	adlVec3 bottom_right_back();
	adlVec3 bottom_right_front();
private:

	adlVec2 min_max_x_;
	adlVec2 min_max_y_;
	adlVec2 min_max_z_;
};

#endif // adl_bounding_box_h__