#include "adlLight_component.h"

#include "../adl_resource/adlResource_manager.h"

adlLight_component::adlLight_component()
	:	light_shader_(nullptr)
{
	light_components_.ambient = adlVec3(0.1f);
	light_components_.diffuse = adlVec3(0.8f);
	light_components_.specular = adlVec3(1.0f);
}

adlLight_component::~adlLight_component()
{
	light_shader_ = nullptr;
}

bool adlLight_component::init(const rapidjson::Value& json_object)
{
	adl_assert(json_object.IsObject());
	const rapidjson::Value& ambient_array = json_object["ambient"];
	const rapidjson::Value& diffuse_array = json_object["diffuse"];
	const rapidjson::Value& specular_array = json_object["specular"];
	const rapidjson::Value& color_array = json_object["color"];

	rapidjson::Value::ConstValueIterator itr = ambient_array.Begin();

	const rapidjson::Value& ambient_x = *itr;
	const rapidjson::Value& ambient_y = *++itr;
	const rapidjson::Value& ambient_z = *++itr;
	light_components_.ambient = adlVec3(ambient_x.GetFloat(), ambient_y.GetFloat(), ambient_z.GetFloat());

	itr = diffuse_array.Begin();

	const rapidjson::Value& diffuse_x = *itr;
	const rapidjson::Value& diffuse_y = *++itr;
	const rapidjson::Value& diffuse_z = *++itr;
	light_components_.diffuse = adlVec3(diffuse_x.GetFloat(), diffuse_y.GetFloat(), diffuse_z.GetFloat());

	itr = specular_array.Begin();

	const rapidjson::Value& specular_x = *itr;
	const rapidjson::Value& specular_y = *++itr;
	const rapidjson::Value& specular_z = *++itr;
	light_components_.specular = adlVec3(specular_x.GetFloat(), specular_y.GetFloat(), specular_z.GetFloat());

	itr = color_array.Begin();

	const rapidjson::Value& color_r = *itr;
	const rapidjson::Value& color_g = *++itr;
	const rapidjson::Value& color_b = *++itr;
	color_ = adlColor(color_r.GetFloat(), color_g.GetFloat(), color_b.GetFloat());

	adlResource_manager* adl_rm = &adlResource_manager::get();
	set_shader(adl_rm->get_shader("light_shader"));

	return true;
}

void adlLight_component::set_ambient(const adlVec3& ambient)
{
	light_components_.ambient = ambient;
}

const adlVec3& adlLight_component::get_ambient()
{
	return light_components_.ambient;
}

void adlLight_component::set_diffuse(const adlVec3& diffuse)
{
	light_components_.diffuse = diffuse;
}
const adlVec3& adlLight_component::get_diffuse()
{
	return light_components_.diffuse;
}

void adlLight_component::set_specular(const adlVec3& specular)
{
	light_components_.specular = specular;
}

const adlVec3& adlLight_component::get_specular()
{
	return light_components_.specular;
}

const adlShader_shared_ptr adlLight_component::get_shader()
{
	return light_shader_;
}

void adlLight_component::set_shader(const adlShader_shared_ptr shader)
{
	light_shader_ = shader;
}

void adlLight_component::set_color(const adlColor& color)
{
	color_ = color;
}

adlColor adlLight_component::get_color()
{
	return color_;
}
