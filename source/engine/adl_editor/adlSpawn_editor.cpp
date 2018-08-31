#include "adlSpawn_editor.h" 
#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlResource_manager.h"

 
adlSpawn_editor::adlSpawn_editor() {
 
}  
 
adlSpawn_editor::~adlSpawn_editor() {
 
}

void adlSpawn_editor::init() {
	spawnTransform.scale = adlVec3(1.0f);
}

void adlSpawn_editor::update(adlScene_manager* scene_manager)
{
	visible = true;
	adlEntity_factory* factory = &adlEntity_factory::get();
	adlResource_manager* adl_rm = &adlResource_manager::get();
	
	const std::vector<std::string> actors = factory->get_all_registered_actors();
	const std::vector<std::string> lights = factory->get_all_registered_lights();

	ImGui::Begin("Spawn Editor");

	if (ImGui::CollapsingHeader("Actors"))
	{
		ImGui::Indent();

		for (size_t i = 0; i < actors.size(); i++)
		{

			if (ImGui::CollapsingHeader(actors[i].data()))
			{
				ImGui::Indent();

				adlVec3 actor_position = spawnTransform.o;
				adlVec3 actor_rotation = spawnTransform.rot;
				adlVec3 actor_scale = spawnTransform.scale;

				if (ImGui::CollapsingHeader("Transform"))
				{
					ImGui::Indent();

					if (ImGui::CollapsingHeader("Position"))
					{
						ImGui::Text("Position(x,y,z)");

						std::string label = actors[i] + " Pos";

						float actorPos[3] = { actor_position.x, actor_position.y, actor_position.z };
						ImGui::InputFloat3(label.data(), &actorPos[0], 2);
						actor_position = adlVec3(actorPos[0], actorPos[1], actorPos[2]);
					}
					if (ImGui::CollapsingHeader("Rotation"))
					{
						ImGui::Text("Rotation(x,y,z)");

						std::string label = actors[i] + " Rot";

						float actorRot[3] = { adlMath::rad_to_deg(actor_rotation.x), adlMath::rad_to_deg(actor_rotation.y), adlMath::rad_to_deg(actor_rotation.z) };
						ImGui::InputFloat3(label.data(), &actorRot[0], 2);
						actor_rotation = adlVec3(adlMath::deg_to_rad(actorRot[0]), adlMath::deg_to_rad(actorRot[1]), adlMath::deg_to_rad(actorRot[2]));
					}
					if (ImGui::CollapsingHeader("Scale"))
					{
						ImGui::Text("Scale(x,y,z)");

						std::string label = actors[i] + " Scale";

						float actorScale[3] = { actor_scale.x, actor_scale.y, actor_scale.z };
						ImGui::InputFloat3(label.data(), &actorScale[0], 2);
						actor_scale = adlVec3(actorScale[0], actorScale[1], actorScale[2]);
					}

					spawnTransform.o = actor_position;
					spawnTransform.rot = actor_rotation;
					spawnTransform.scale = actor_scale;

					ImGui::Unindent();
				}

				if (ImGui::CollapsingHeader("Actor Properties"))
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
								spawnModel = adl_rm->getModel(modelName);

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
								spawnMaterial = adl_rm->get_material(materialName);
							}

							ImGui::Unindent();
						}
						ImGui::Unindent();
					}
					ImGui::Unindent();

				}


				std::string buttonLabel = "Spawn " + actors[i] + " actor";


				if (ImGui::Button(buttonLabel.data()))
				{
					ImGui::Indent();

					adlActor_shared_ptr spawnedActor = scene_manager->spawnActor(actors[i].data(), spawnTransform.o, spawnTransform.rot, spawnTransform.scale);

					if (spawnModel != nullptr)
					{
						spawnedActor->setModel(spawnModel);
						spawnModel = adl_rm->getModel("");

					}

					if (spawnMaterial != nullptr)
					{
						spawnedActor->setMaterial(spawnMaterial);
						spawnMaterial = adl_rm->get_material("");
					}

					visible = false;
					ImGui::Unindent();
				}

				ImGui::Unindent();
			}
		}

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Lights"))
	{
		ImGui::Indent();

		for (size_t i = 0; i < lights.size(); i++)
		{

			if (ImGui::CollapsingHeader(lights[i].data()))
			{
				ImGui::Indent();

				adlVec3 light_position = spawnTransform.o;
				adlVec3 light_rotation = spawnTransform.rot;
				adlVec3 light_scale = spawnTransform.scale;

				if (ImGui::CollapsingHeader("Transform"))
				{
					ImGui::Indent();

					if (ImGui::CollapsingHeader("Position"))
					{
						ImGui::Text("Position(x,y,z)");

						std::string label = lights[i] + " Pos";

						float lightPos[3] = { light_position.x, light_position.y, light_position.z };
						ImGui::InputFloat3(label.data(), &lightPos[0], 2);
						light_position = adlVec3(lightPos[0], lightPos[1], lightPos[2]);
					}
					if (ImGui::CollapsingHeader("Rotation"))
					{
						ImGui::Text("Rotation(x,y,z)");

						std::string label = lights[i] + " Rot";

						float lightRot[3] = { adlMath::rad_to_deg(light_rotation.x), adlMath::rad_to_deg(light_rotation.y), adlMath::rad_to_deg(light_rotation.z) };
						ImGui::InputFloat3(label.data(), &lightRot[0], 2);
						light_rotation = adlVec3(adlMath::deg_to_rad(lightRot[0]), adlMath::deg_to_rad(lightRot[1]), adlMath::deg_to_rad(lightRot[2]));
					}
					if (ImGui::CollapsingHeader("Scale"))
					{
						ImGui::Text("Scale(x,y,z)");

						std::string label = lights[i] + " Scale";

						float lightScale[3] = { light_scale.x, light_scale.y, light_scale.z };
						ImGui::InputFloat3(label.data(), &lightScale[0], 2);
						light_scale = adlVec3(lightScale[0], lightScale[1], lightScale[2]);
					}

					spawnTransform.o = light_position;
					spawnTransform.rot = light_rotation;
					spawnTransform.scale = light_scale;

					ImGui::Unindent();
				}

				std::string buttonLabel = "Spawn " + lights[i] + " light";


				if (ImGui::Button(buttonLabel.data()))
				{
					ImGui::Indent();

					scene_manager->spawn_light(lights[i].data(), spawnTransform.o, spawnTransform.rot, spawnTransform.scale);

					visible = false;
					ImGui::Unindent();
				}

				ImGui::Unindent();
			}
		}

		ImGui::Unindent();
	}

	ImGui::End();
}
