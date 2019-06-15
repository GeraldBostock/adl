#include "adlRender_component.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlModel.h"

adlRender_component::adlRender_component()
	:	model_(nullptr),
		material_(nullptr)
{
	REGISTER_COMPONENT(adlRender_component)
	engine_component_name = "adlRender_component";

	adlResource_manager* adl_rm = &adlResource_manager::get();
	model_ = adl_rm->get_model("Cube");
	material_ = adl_rm->get_material("copper");
}

bool adlRender_component::init(const rapidjson::Value& json_object)
{
	adlResource_manager* adl_rm = &adlResource_manager::get();

	std::string model_name = json_object["model"].GetString();
	if (json_object.HasMember("material"))
	{
		std::string material_name = json_object["material"].GetString();
		material_ = adl_rm->get_material(material_name);
	}

	model_ = adl_rm->get_model(model_name);

	return true;
}

void adlRender_component::destroy()
{
	model_ = nullptr;
	material_ = nullptr;
}

void adlRender_component::editor()
{
	ImGui::Indent();

	if (ImGui::CollapsingHeader("Model"))
	{
		ImGui::Indent();

		static char model_name[20] = {};

		ImGui::Text("Model(Name)");
		ImGui::InputText("(max 20 char)", model_name, sizeof(model_name));
		if (ImGui::Button("Refresh Mesh"))
		{
			adlResource_manager* adl_rm = &adlResource_manager::get();
			adlModel_shared_ptr model = adl_rm->get_model(model_name);
			if (model != nullptr)
			{
				model_ = model;
			}
		}
		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Indent();

		static char material_name[20] = {};

		ImGui::Text(std::string("Material(Name) - " + material_->get_name()).c_str());
		ImGui::InputText("(max 20 char)", material_name, sizeof(material_name));

		if (ImGui::Button("Refresh Material"))
		{
			adlResource_manager* adl_rm = &adlResource_manager::get();
			adlMaterial_shared_ptr material = adl_rm->get_material(material_name);
			if (material != nullptr)
			{
				material_ = material;
				model_->set_material(material_);
			}
		}


		ImGui::Unindent();
	}

	ImGui::Unindent();
}

adlModel_shared_ptr adlRender_component::get_model()
{
	return model_;
}

adlMaterial_shared_ptr adlRender_component::get_material()
{
	return material_;
}