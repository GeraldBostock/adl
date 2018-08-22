#include "adlMaterial.h"

#include "engine/adl_resource/adlStatic_shader.h"


adlMaterial::adlMaterial()
	: shader_(nullptr)
{
}


adlMaterial::~adlMaterial()
{
}

void adlMaterial::set_material(adlVec3 ambient, adlVec3 diffuse, adlVec3 specular, float shininess)
{
	material_.ambient = ambient;
	material_.diffuse = diffuse;
	material_.specular = specular;
	material_.shininess = shininess;
}

void adlMaterial::set_shader(adlShader_shared_ptr shader)
{
	shader_ = shader;
}

adlVec3 adlMaterial::get_ambient()
{
	return material_.ambient;
}

adlVec3 adlMaterial::get_diffuse()
{
	return material_.diffuse;
}
adlVec3 adlMaterial::get_specular()
{
	return material_.specular;
}

float adlMaterial::get_shininess()
{
	return material_.shininess;
}

void adlMaterial::set_shader_name(const std::string& shader_name)
{
	shader_name_ = shader_name;
}

adlShader_shared_ptr adlMaterial::get_shader()
{
	return shader_;
}

std::string adlMaterial::get_shader_name()
{
	return shader_name_;
}
