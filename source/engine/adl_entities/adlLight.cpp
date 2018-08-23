#include "adlLight.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlStatic_shader.h"

adlLight::adlLight()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	light_shader_ = adl_rm->get_shader("light_shader");
	model_ = adl_rm->get_model("cube");
	setPosition(adlVec3(0));
	setRotation(adlVec3(0));
	setScale(adlVec3(0.15f));
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

adlShader_shared_ptr adlLight::getShader()
{
	return get_shader();
}

adlVec3 adlLight::getAmbient()
{
	return get_ambient();
}

adlVec3 adlLight::getDiffuse()
{
	return get_diffuse();
}

adlVec3 adlLight::getSpecular()
{
	return get_specular();
}