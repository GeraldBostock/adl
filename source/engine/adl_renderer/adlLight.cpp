#include "adlLight.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlStatic_shader.h"

adlLight::adlLight(adlModel_shared_ptr model, adlColor color)
{
	light_model_ = model;
	light_color_ = color;
	adlResource_manager* adl_rm = &adlResource_manager::get();
	light_shader_ = adl_rm->get_shader("light_shader");
}

adlLight::~adlLight()
{

}

adlModel_shared_ptr adlLight::get_model()
{
	return light_model_;
}

adlColor adlLight::get_color()
{
	return light_color_;
}

adlMatrix_frame adlLight::get_frame()
{
	return frame_;
}

void adlLight::set_frame(adlMatrix_frame frame)
{
	frame_.o = frame.o;
	frame_.rot = frame.rot;
	frame_.scale = frame.scale;
}

adlShader_shared_ptr adlLight::get_shader()
{
	return light_shader_;
}