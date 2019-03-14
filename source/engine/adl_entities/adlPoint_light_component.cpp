#include "adlPoint_light_component.h"

adlPoint_light_component::adlPoint_light_component()
	:	constant_(1.0f),
		linear_(0.022f),
		quadratic_(0.0018f)
{
	REGISTER_COMPONENT(adlPoint_light_component);
}

adlPoint_light_component::~adlPoint_light_component()
{

}

bool adlPoint_light_component::init(const rapidjson::Value& json_object)
{
	adlLight_component::init(json_object);

	const rapidjson::Value& constant = json_object["constant"];
	const rapidjson::Value& linear = json_object["linear"];
	const rapidjson::Value& quadratic = json_object["quadratic"];

	constant_ = constant.GetFloat();
	linear_ = linear.GetFloat();
	quadratic_ = quadratic.GetFloat();

	return true;
}

float adlPoint_light_component::get_constant() const
{
	return constant_;
}

void adlPoint_light_component::set_constant(float constant)
{
	constant_ = constant;
}

float adlPoint_light_component::get_linear() const
{
	return linear_;
}

void adlPoint_light_component::set_linear(float linear)
{
	linear_ = linear;
}

float adlPoint_light_component::get_quadratic() const
{
	return quadratic_;
}

void adlPoint_light_component::set_quadratic(float quadratic)
{
	quadratic_ = quadratic;
}
