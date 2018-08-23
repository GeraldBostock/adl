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

	light_components_.ambient = adlVec3(0.2f);
	light_components_.diffuse = adlVec3(0.5f);
	light_components_.specular = adlVec3(1.0f);

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

adlShader_shared_ptr adlLight::get_shader()
{
	return light_shader_;
}

adlVec3 adlLight::get_ambient()
{
	return light_components_.ambient;
}

adlVec3 adlLight::get_diffuse()
{
	return light_components_.diffuse;
}

adlVec3 adlLight::get_specular()
{
	return light_components_.specular;
}

