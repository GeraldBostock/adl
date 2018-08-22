#include "Test_light.h"


Test_light::Test_light()
{
}


Test_light::~Test_light()
{
}

void Test_light::init()
{
	transform_.o = adlVec3(0, 0, 4);
	color_ = adlColor::WHITE;
	timer_.start();
}

void Test_light::update(float dt)
{
	transform_.o.x = std::sin(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds() / 8)) * 5 + 2;
}
