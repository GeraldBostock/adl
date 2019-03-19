#include "adlResource_manager_editor.h"

#include "engine/adl_resource/adlResource_manager.h"

adlResource_manager_editor::adlResource_manager_editor()
{
	loaded_color_ = ImVec4(0, 255, 0, 255);
	not_loaded_color_ = ImVec4(165, 165, 165, 255);
}

adlResource_manager_editor::~adlResource_manager_editor()
{

}

void adlResource_manager_editor::update()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();

	ImGui::Begin("Resources");

	if (ImGui::CollapsingHeader("Models"))
	{
		ImGui::Indent();
		for (std::map<std::string, std::string>::const_iterator it = adl_rm->name_to_model_path_.begin(); it != adl_rm->name_to_model_path_.end(); ++it)
		{
			if (adl_rm->models_[it->second] == nullptr)
			{
				ImGui::PushStyleColor(0, not_loaded_color_);
			}
			else
			{
				ImGui::PushStyleColor(0, loaded_color_);
			}
			if (ImGui::CollapsingHeader(it->first.c_str()))
			{
				if (adl_rm->models_[it->second])
				{
					ImGui::Indent();
					if (ImGui::Button("Reload"))
					{
						adl_rm->reload_resource(it->first, Resources::MODEL);
					}
					ImGui::Unindent();
				}
				else
				{
					ImGui::Indent();
					if (ImGui::Button("Load"))
					{
						adl_rm->reload_resource(it->first, Resources::MODEL);
					}
					ImGui::Unindent();
				}
			}
			ImGui::PopStyleColor();
		}
		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Entities"))
	{
		ImGui::Indent();
		for (std::map<std::string, std::string>::const_iterator it = adl_rm->name_to_entity_path_.begin(); it != adl_rm->name_to_entity_path_.end(); ++it)
		{
			if (adl_rm->entity_json_string_[it->first] == "")
			{
				ImGui::PushStyleColor(0, not_loaded_color_);
			}
			else
			{
				ImGui::PushStyleColor(0, loaded_color_);
			}
			if (ImGui::CollapsingHeader(it->first.c_str()))
			{
				if (adl_rm->entity_json_string_[it->first] != "")
				{
					ImGui::Indent();
					if (ImGui::Button("Reload"))
					{
						adl_rm->reload_resource(it->first, Resources::ENTITY);
					}
					ImGui::Unindent();
				}
				else
				{
					ImGui::Indent();
					if (ImGui::Button("Load"))
					{
						adl_rm->reload_resource(it->first, Resources::ENTITY);
					}
					ImGui::Unindent();
				}
			}
			ImGui::PopStyleColor();
		}
		ImGui::Unindent();
	}

	ImGui::End();
}