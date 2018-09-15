#include "adlMaterial.h"

#include "engine/adl_resource/adlStatic_shader.h"
#include "engine/adl_resource/adlTexture.h"


adlMaterial::adlMaterial()
	: shader_(nullptr),
	  texture_(nullptr)
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

void adlMaterial::set_names(const std::string& shader_name, const std::string& texture_name)
{
	shader_name_ = shader_name;
	texture_name_ = texture_name;
}

adlTexture_shared_ptr adlMaterial::get_texture()
{
	return texture_;
}

void adlMaterial::set_texture(adlTexture_shared_ptr texture)
{
	texture_ = texture;
}

std::string adlMaterial::get_texture_name()
{
	return texture_name_;
}

const std::string& adlMaterial::get_name()
{
	return name_;
}

void adlMaterial::set_name(const std::string& name)
{
	name_ = name;
}
