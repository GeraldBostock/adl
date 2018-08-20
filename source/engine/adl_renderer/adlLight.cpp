#include "adlLight.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlStatic_shader.h"

adlLight::adlLight()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	light_shader_ = adl_rm->get_shader("light_shader");
	model_ = adl_rm->get_model("cube");
	transform_ = adlTransform::identity();
	transform_.scale = adlVec3(0.15f);
	color_ = adlColor::WHITE;
}

adlLight::~adlLight()
{

}

void adlLight::init()
{

}

void adlLight::update(float dt)
{

}

//void adlLight::set_frame(adlMatrix_frame frame)
//{
//	frame_.o = frame.o;
//	frame_.rot = frame.rot;
//	frame_.scale = frame.scale;
//}

adlShader_shared_ptr adlLight::get_shader()
{
	return light_shader_;
}
