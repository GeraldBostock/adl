#include "adlRender_component.h"

#include "engine/adl_resource/adlResource_manager.h"

adlRender_component::adlRender_component()
	:	model_(nullptr),
		material_(nullptr)
{
	REGISTER_COMPONENT(adlRender_component)
}

bool adlRender_component::init(const rapidjson::Value& json_object)
{
	std::string model_name = json_object["model"].GetString();
	std::string material_name = json_object["material"].GetString();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	model_ = adl_rm->get_model(model_name);
	material_ = adl_rm->get_material(material_name);

	return true;
}

void adlRender_component::destroy()
{
	model_ = nullptr;
	material_ = nullptr;
}

adlModel_shared_ptr adlRender_component::get_model()
{
	return model_;
}

adlMaterial_shared_ptr adlRender_component::get_material()
{
	return material_;
}

void adlRender_component::set_material(adlMaterial_shared_ptr mat)
{
	material_ = mat;
}

void adlRender_component::set_model(adlModel_shared_ptr model)
{
	model_ = model;
}