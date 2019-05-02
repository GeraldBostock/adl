#include "adlBounding_box.h"


adlBounding_box::adlBounding_box(adlVec2 min_max_x, adlVec2 min_max_y, adlVec2 min_max_z)
	:	min_max_x_(min_max_x),
		min_max_y_(min_max_y),
		min_max_z_(min_max_z)
{
	points_.push_back(up_left_back());
	points_.push_back(up_left_front());
	points_.push_back(up_right_back());
	points_.push_back(up_right_front());

	points_.push_back(bottom_left_back());
	points_.push_back(bottom_left_front());
	points_.push_back(bottom_right_back());
	points_.push_back(bottom_right_front());
}


adlBounding_box::~adlBounding_box()
{
}

adlVec3 adlBounding_box::up_left_back()
{
	return adlVec3(min_max_x_.x, min_max_y_.y, min_max_z_.x);
}

adlVec3 adlBounding_box::up_left_front()
{
	return adlVec3(min_max_x_.x, min_max_y_.y, min_max_z_.y);
}

adlVec3 adlBounding_box::up_right_back()
{
	return adlVec3(min_max_x_.y, min_max_y_.y, min_max_z_.x);
}

adlVec3 adlBounding_box::up_right_front()
{
	return adlVec3(min_max_x_.y, min_max_y_.y, min_max_z_.y);
}

adlVec3 adlBounding_box::bottom_left_back()
{
	return adlVec3(min_max_x_.x, min_max_y_.x, min_max_z_.x);
}

adlVec3 adlBounding_box::bottom_left_front()
{
	return adlVec3(min_max_x_.x, min_max_y_.x, min_max_z_.y);
}

adlVec3 adlBounding_box::bottom_right_back()
{
	return adlVec3(min_max_x_.y, min_max_y_.x, min_max_z_.x);
}

adlVec3 adlBounding_box::bottom_right_front()
{
	return adlVec3(min_max_x_.y, min_max_y_.x, min_max_z_.y);
}

const std::vector<adlVec3>& adlBounding_box::get_points()
{
	return points_;
}
