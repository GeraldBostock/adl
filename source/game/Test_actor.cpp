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
	model_ = adl_rm->get_model("cube");
	adlShader_shared_ptr shader = adl_rm->get_shader("phong_shader");
	model_->set_shader(shader);

	transform_.o = adlVec3(0.0f, 0.0f, 0.0f);
	transform_.rot = adlVec3(0.0f);
	transform_.scale = adlVec3(1.0f);

	color_ = adlColor(160, 82, 45);
}

void Test_actor::update(float dt)
{
	//transform_.rot.y = transform_.rot.y + adlMath::deg_to_rad(0.1f * dt);
}
