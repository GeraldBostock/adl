#include "adlEntity_editor.h" 
#include "engine/adl_debug/imgui/imgui.h"

 
adlEntity_editor::adlEntity_editor() {  
 
}  
 
adlEntity_editor::~adlEntity_editor() {  
 
}

void adlEntity_editor::update(std::vector<adlEntity_shared_ptr>& entities)
{
	adlEntity_factory* fac = &adlEntity_factory::get();
	std::vector<std::string> component_names = fac->get_all_registered_entities();

	ImGui::Begin("Entity Editor");
	ImGui::Text("Entities\n");

	if (ImGui::CollapsingHeader("Entities"))
	{
		ImGui::Indent();

		for (unsigned int i = 0; i < entities.size(); i++)
		{
			std::string actr = entities[i]->get_name();
			//This might cause problems for entities with the same name
			if (ImGui::CollapsingHeader(actr.c_str()))
			{
				ImGui::Indent();
				ImGui::Text("Entity (%d)", i);

				ImGui::Indent();
				if (ImGui::CollapsingHeader("Add Components"))
				{
					for (auto component_name : component_names)
					{
						if (!entities[i]->has_component(component_name))
						{
							ImGui::Indent();
							if (ImGui::Button(component_name.c_str()))
							{
								fac->add_component_to_entity(entities[i], component_name);
							}
							ImGui::Unindent();
						}
					}
				}
				ImGui::Unindent();

				for (auto component : entities[i]->get_all_components())
				{
					if (!component)
					{
						continue;
					}
					adl_assert(component);
					ImGui::Indent();
					if (ImGui::CollapsingHeader(component->get_type_name().c_str()))
					{
						component->editor();

						ImGui::PushStyleColor(0, ImVec4(255, 0, 0, 255));
						ImGui::Indent();
						if(ImGui::Button("Remove Component"))
						{
							fac->remove_component_from_entity(entities[i], component->get_type_name());
						}
						ImGui::Unindent();
						ImGui::PopStyleColor();
					}
					ImGui::Unindent();
				}

				ImGui::Unindent();
			}
		}
		ImGui::Unindent();
	}

	ImGui::End();
}
