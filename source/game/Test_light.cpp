#include "Test_light.h"

#include "engine/adl_entities/adlEntity_factory.h"

Test_light::Test_light()
{
	REGISTER_CLASS(Test_light)
}


Test_light::~Test_light()
{
}

void Test_light::init()
{
	set_position(adlVec3(0, 5, 4));
	timer_.start();
}

void Test_light::update(float dt)
{
}
