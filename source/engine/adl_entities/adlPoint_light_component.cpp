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

void adlPoint_light_component::editor()
{
	ImGui::Indent();
	ImGui::Text("Light Attributes");

	float light_ambient[3] = { light_components_.ambient.x, light_components_.ambient.y, light_components_.ambient.z };
	if (ImGui::ColorEdit3("Ambient", light_ambient))
	{
		adlVec3 ambient(light_ambient[0], light_ambient[1], light_ambient[2]);
		set_ambient(ambient);
	}

	float light_diffuse[3] = { light_components_.diffuse.x, light_components_.diffuse.y, light_components_.diffuse.z };
	if (ImGui::ColorEdit3("Diffuse", light_diffuse))
	{
		adlVec3 diffuse(light_diffuse[0], light_diffuse[1], light_diffuse[2]);
		set_diffuse(diffuse);
	}

	float light_specular[3] = { light_components_.specular.x, light_components_.specular.y, light_components_.specular.z };
	if (ImGui::ColorEdit3("Specular", light_specular))
	{
		adlVec3 specular(light_specular[0], light_specular[1], light_specular[2]);
		set_specular(specular);
	}

	ImGui::Indent();
	ImGui::Text("Constant(0f, 50f)");
	ImGui::SliderFloat("##Constant", &constant_, 0.0f, 50.0f);
	ImGui::Unindent();

	ImGui::Indent();
	ImGui::Text("Linear(0f, 1f)");
	ImGui::SliderFloat("##Linear", &linear_, 0.0f, 1.0f);
	ImGui::Unindent();

	ImGui::Indent();
	ImGui::Text("Quadratic(0f, 1f)");
	ImGui::SliderFloat("##Quadratic", &quadratic_, 0.0f, 1.0f);
	ImGui::Unindent();

	ImGui::Unindent();
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
