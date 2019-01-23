#include "Test_actor.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_entities/adlEntity_factory.h"

Test_actor::Test_actor()
{
	REGISTER_ACTOR(Test_actor)
}


Test_actor::~Test_actor()
{
}

void Test_actor::init()
{
	set_position(adlVec3(0.0f, -5.0f, 0.0f));
	set_rotation(adlVec3(0, 0, 0));
	set_scale(adlVec3(1.0f, 1.0f, 1.0f));

	color_ = adlColor(160, 82, 45);
}

void Test_actor::update(float dt)
{
}

void Test_actor::deserialize(const rapidjson::Value& json_object)
{
}
