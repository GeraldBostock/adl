#include "Test_light.h"


Test_light::Test_light()
{
}


Test_light::~Test_light()
{
}

void Test_light::init()
{
	set_position(adlVec3(0, 5, 4));
	color_ = adlColor::WHITE;
	timer_.start();
}

void Test_light::update(float dt)
{
	adlVec3 position = get_position();
	position.x = std::sin(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds() / 20)) * 30 + 15;
	set_position(position);
}
