#include "Test_light.h"


Test_light::Test_light()
{
}


Test_light::~Test_light()
{
}

void Test_light::init()
{
	transform_.o = adlVec3(0, 0, -4);
	color_ = adlColor::WHITE;
}

void Test_light::update(float dt)
{
	transform_.o = adlMath::rotate_around(adlMath::deg_to_rad(0.15f * dt), transform_.o, adlVec3(0, 5, 0));
}
