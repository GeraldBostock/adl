#include "Test_actor.h"

#include "engine/adl_resource/adlResource_manager.h"

Test_actor::Test_actor()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->get_model("landscape"));
	setMaterial(adl_rm->get_material("copper"));

	setPosition(adlVec3(0.0f, -5.0f, 0.0f));
	setRotation(adlVec3(0.0f));
	setScale(1.0f);

	color_ = adlColor(160, 82, 45);
}


Test_actor::~Test_actor()
{
}

void Test_actor::init()
{

}

void Test_actor::update(float dt)
{
	//transform_.rot.y = transform_.rot.y + adlMath::deg_to_rad(0.1f * dt);
}
