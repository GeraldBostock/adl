#include "adlLight.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlStatic_shader.h"

adlLight::adlLight()
{
}

adlLight::~adlLight()
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

void adlLight::setShader(adlShader_shared_ptr shader)
{
	set_shader(shader);
}

void adlLight::set_shader(adlShader_shared_ptr shader)
{
	light_shader_ = shader;
}

void adlLight::setAmbient(adlVec3 ambient)
{
	set_ambient(ambient);
}

void adlLight::set_ambient(adlVec3 ambient)
{
	light_components_.ambient = ambient;
}

void adlLight::setDiffuse(adlVec3 diffuse)
{
	set_diffuse(diffuse);
}

void adlLight::set_diffuse(adlVec3 diffuse)
{
	light_components_.diffuse = diffuse;
}

void adlLight::setSpecular(adlVec3 specular)
{
	set_specular(specular);
}

void adlLight::set_specular(adlVec3 specular)
{
	light_components_.specular = specular;
}