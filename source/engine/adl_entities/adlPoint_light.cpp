#include "adlPoint_light.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlInput.h"
#include "adlEntity_factory.h"

adlPoint_light::adlPoint_light()
{
	REGISTER_CLASS(adlPoint_light)

	adlResource_manager* adl_rm = &adlResource_manager::get();
	set_shader(adl_rm->get_shader("light_shader"));
	set_model(adl_rm->get_model("cube"));
	set_position(adlVec3(0, 0, -5));
	set_rotation(adlVec3(0));
	set_scale(adlVec3(0.15f));
	color_ = adlColor::WHITE;

	light_components_.ambient = adlVec3(0.2f);
	light_components_.diffuse = adlVec3(1.0f);
	light_components_.specular = adlVec3(1.0f);

	set_constant(1.0f);
	set_linear(0.022f);
	set_quadratic(0.0018f);
}


adlPoint_light::~adlPoint_light()
{
}

void adlPoint_light::init()
{

}

void adlPoint_light::update(float dt)
{
	adlInput* input = &adlInput::get();
	adlVec3 position = get_position();

	if (input->get_key(adl_key_up))
	{
		position.z -= dt * 0.01f;
	}
	if (input->get_key(adl_key_down))
	{
		position.z += dt * 0.01f;
	}
	if (input->get_key(adl_key_right))
	{
		position.x += dt * 0.01f;
	}
	if (input->get_key(adl_key_left))
	{
		position.x -= dt * 0.01f;
	}

	set_position(position);
}

void adlPoint_light::set_constant(float constant)
{
	constant_ = constant;
}

float adlPoint_light::get_constant()
{
	return constant_;
}

void adlPoint_light::set_linear(float linear)
{
	linear_ = linear;
}

float adlPoint_light::get_linear()
{
	return linear_;
}

void adlPoint_light::set_quadratic(float quadratic)
{
	quadratic_ = quadratic;
}

float adlPoint_light::get_quadratic()
{
	return quadratic_;
}