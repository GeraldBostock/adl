#include "Test_actor.h"

#include "engine/adl_resource/adlResource_manager.h"

Test_actor::Test_actor()
{
}


Test_actor::~Test_actor()
{
}

void Test_actor::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->get_model("landscape"));
	adlMaterial_shared_ptr material = adl_rm->get_material("copper");
	set_material(material);

	set_position(adlVec3(0.0f, -5.0f, 0.0f));
	set_rotation(adlVec3(adlMath::deg_to_rad(-90.0f), 0, 0));
	set_scale(1.0f);

	color_ = adlColor(160, 82, 45);
}

void Test_actor::update(float dt)
{
	//transform_.rot.y = transform_.rot.y + adlMath::deg_to_rad(0.1f * dt);
}
