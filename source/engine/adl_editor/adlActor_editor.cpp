#include "adlActor_editor.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adl_entities/adlActor.h"
#include "engine/adl_resource/adlResource_manager.h"

adlActor_editor::adlActor_editor()
{
}


adlActor_editor::~adlActor_editor()
{
}


void adlActor_editor::update(std::vector<adlActor_shared_ptr>& actors)
{
	ImGui::Begin("Actor Editor");
	ImGui::Text("Actors");

	if (ImGui::CollapsingHeader("Actors"))
	{
		ImGui::Indent();

		for (size_t i = 0; i < actors.size(); i++)
		{
			std::string actr = "Actor " + std::to_string(i + 1);
			if (ImGui::CollapsingHeader(actr.data()))
			{
				ImGui::Indent();
				ImGui::Text("Actors (%d)", i);
				actorStats(actors[i], i);
				ImGui::Unindent();
			}
		}
		ImGui::Unindent();
	}

	ImGui::End();
}

void adlActor_editor::actorStats(adlActor_shared_ptr actor, int index)
{
	adlVec3 actor_position = actor->getPosition();
	adlVec3 actor_rotation = actor->getRotation();
	adlVec3 actor_scale = actor->getScale();

	if (ImGui::CollapsingHeader("Transform "))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Position"))
		{
			ImGui::Text("Position(x,y,z)");

			std::string label = "##ActorPos" + std::to_string(index + 1);

			float actorPos[3] = { actor_position.x, actor_position.y, actor_position.z };
			ImGui::InputFloat3(label.data(), &actorPos[0], 2);
			actor_position = adlVec3(actorPos[0], actorPos[1], actorPos[2]);
			actor->set_position(actor_position);
		}
		if (ImGui::CollapsingHeader("Rotation"))
		{
			ImGui::Text("Rotation(x,y,z)");

			std::string label = "##ActorRot" + std::to_string(index + 1);

			float actorRot[3] = { actor_rotation.x, actor_rotation.y, actor_rotation.z };
			ImGui::InputFloat3(label.data(), &actorRot[0], 2);
			actor_rotation = adlVec3(adlMath::deg_to_rad(actorRot[0]), adlMath::deg_to_rad(actorRot[1]), adlMath::deg_to_rad(actorRot[2]));
			actor->set_rotation(actor_rotation);
		}
		if (ImGui::CollapsingHeader("Scale"))
		{
			ImGui::Text("Scale(x,y,z)");

			std::string label = "##ActorScale" + std::to_string(index + 1);

			float actorScale[3] = { actor_scale.x, actor_scale.y, actor_scale.z };
			ImGui::InputFloat3(label.data(), &actorScale[0], 2);
			actor_scale = adlVec3(actorScale[0], actorScale[1], actorScale[2]);
			actor->setScale(actor_scale);
		}
		ImGui::Unindent();
	}
	if (ImGui::CollapsingHeader("Actor Abilities"))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader("Model"))
		{
			ImGui::Indent();

			if (ImGui::CollapsingHeader("Mesh"))
			{
				ImGui::Indent();

				static char modelName[20] = {};

				ImGui::Text("Mesh(Name)");
				ImGui::InputText("(max 20 char)", modelName, sizeof(modelName));
				if (ImGui::Button("Refresh Mesh"))
				{
					adlResource_manager* adl_rm = &adlResource_manager::get();
					adlModel_shared_ptr model = adl_rm->getModel(modelName);
					if (model != nullptr)
					{
						actor->setModel(model);
					}
				}
				ImGui::Unindent();
			}
			if (ImGui::CollapsingHeader("Material"))
			{
				ImGui::Indent();

				static char materialName[20] = {};

				ImGui::Text("Material(Name)");
				ImGui::InputText("(max 20 char)", materialName, sizeof(materialName));

				if (ImGui::Button("Refresh Material"))
				{
					adlResource_manager* adl_rm = &adlResource_manager::get();
					adlMaterial_shared_ptr material = adl_rm->get_material(materialName);
					if (material != nullptr)
					{
						actor->setMaterial(material);
					}
				}


				ImGui::Unindent();
			}
			ImGui::Unindent();
		}
		ImGui::Unindent();

	}
}
