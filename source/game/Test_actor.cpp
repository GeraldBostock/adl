#include "Test_actor.h"

#include "engine/adl_resource/adlResource_manager.h"

Test_actor::Test_actor()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	model_ = adl_rm->get_model("cube");
	adlMaterial_shared_ptr material = adl_rm->get_material("copper");
	setMaterial(material);

	setTransform(adlTransform(adlVec3(0.0f, 0.0f, 0.0f), adlVec3(0.0f), adlVec3(1.0f)));

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
