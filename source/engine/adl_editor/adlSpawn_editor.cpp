#include "adlSpawn_editor.h" 
#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_resource/adlResource_manager.h"

 
adlSpawn_editor::adlSpawn_editor() 
{
}  
 
adlSpawn_editor::~adlSpawn_editor() 
{
}

void adlSpawn_editor::init() 
{
	spawn_transform_.scale = adlVec3(1.0f);
}

void adlSpawn_editor::update(adlScene_manager* scene_manager)
{
	is_visible_ = true;
	adlEntity_factory* factory = &adlEntity_factory::get();
	adlResource_manager* adl_rm = &adlResource_manager::get();
	
	const std::vector<std::string>& entities = adl_rm->get_all_entity_names();

	ImGui::Begin("Spawn Editor");

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		ImGui::Indent();

		if (ImGui::Button(entities[i].c_str()))
		{
			scene_manager->add_entity_to_scene(entities[i].c_str());
			//factory->construct_entity(entities[i]);
		}

		ImGui::Unindent();
	}

	ImGui::End();
	//ImGui::Begin("Spawn Editor");

	//if (ImGui::CollapsingHeader("Entities"))
	//{
	//	ImGui::Indent();

	//	for (size_t i = 0; i < actors.size(); i++)
	//	{

	//		if (ImGui::CollapsingHeader(actors[i].data()))
	//		{
	//			ImGui::Indent();

	//			adlVec3 actor_position = spawn_transform_.o;
	//			adlVec3 actor_rotation = spawn_transform_.rot;
	//			adlVec3 actor_scale = spawn_transform_.scale;

	//			if (ImGui::CollapsingHeader("Transform"))
	//			{
	//				ImGui::Indent();

	//				if (ImGui::CollapsingHeader("Position"))
	//				{
	//					ImGui::Text("Position(x,y,z)");

	//					std::string label = actors[i] + " Pos";

	//					float actorPos[3] = { actor_position.x, actor_position.y, actor_position.z };
	//					ImGui::InputFloat3(label.data(), &actorPos[0], 2);
	//					actor_position = adlVec3(actorPos[0], actorPos[1], actorPos[2]);
	//				}
	//				if (ImGui::CollapsingHeader("Rotation"))
	//				{
	//					ImGui::Text("Rotation(x,y,z)");

	//					std::string label = actors[i] + " Rot";

	//					float actorRot[3] = { adlMath::rad_to_deg(actor_rotation.x), adlMath::rad_to_deg(actor_rotation.y), adlMath::rad_to_deg(actor_rotation.z) };
	//					ImGui::InputFloat3(label.data(), &actorRot[0], 2);
	//					actor_rotation = adlVec3(adlMath::deg_to_rad(actorRot[0]), adlMath::deg_to_rad(actorRot[1]), adlMath::deg_to_rad(actorRot[2]));
	//				}
	//				if (ImGui::CollapsingHeader("Scale"))
	//				{
	//					ImGui::Text("Scale(x,y,z)");

	//					std::string label = actors[i] + " Scale";

	//					float actorScale[3] = { actor_scale.x, actor_scale.y, actor_scale.z };
	//					ImGui::InputFloat3(label.data(), &actorScale[0], 2);
	//					actor_scale = adlVec3(actorScale[0], actorScale[1], actorScale[2]);
	//				}

	//				spawn_transform_.o = actor_position;
	//				spawn_transform_.rot = actor_rotation;
	//				spawn_transform_.scale = actor_scale;

	//				ImGui::Unindent();
	//			}

	//			if (ImGui::CollapsingHeader("Actor Properties"))
	//			{
	//				ImGui::Indent();
	//				if (ImGui::CollapsingHeader("Model"))
	//				{
	//					ImGui::Indent();

	//					if (ImGui::CollapsingHeader("Mesh"))
	//					{
	//						ImGui::Indent();

	//						static char model_name[20] = {};

	//						ImGui::Text("Mesh(Name)");
	//						ImGui::InputText("(max 20 char)", model_name, sizeof(model_name));
	//						if (ImGui::Button("Refresh Mesh"))
	//						{
	//							spawn_model_ = adl_rm->get_model(model_name);

	//						}
	//						ImGui::Unindent();
	//					}
	//					if (ImGui::CollapsingHeader("Material"))
	//					{
	//						ImGui::Indent();

	//						static char material_name[20] = {};

	//						ImGui::Text("Material(Name)");
	//						ImGui::InputText("(max 20 char)", material_name, sizeof(material_name));

	//						if (ImGui::Button("Refresh Material"))
	//						{
	//							spawn_material_ = adl_rm->get_material(material_name);
	//						}

	//						ImGui::Unindent();
	//					}
	//					ImGui::Unindent();
	//				}
	//				ImGui::Unindent();

	//			}


	//			std::string button_label = "Spawn " + actors[i] + " actor";


	//			if (ImGui::Button(button_label.data()))
	//			{
	//				ImGui::Indent();

	//				//adlActor_shared_ptr spawned_actor = scene_manager->spawn_actor(actors[i].data(), spawn_transform_.o, spawn_transform_.rot, spawn_transform_.scale);

	//				if (spawn_model_ != nullptr)
	//				{
	//					//spawned_actor->set_model(spawn_model_);
	//					spawn_model_ = adl_rm->get_model("");

	//				}

	//				if (spawn_material_ != nullptr)
	//				{
	//					//spawned_actor->set_material(spawn_material_);
	//					spawn_material_ = adl_rm->get_material("");
	//				}

	//				//is_visible_ = false;
	//				ImGui::Unindent();
	//			}

	//			ImGui::Unindent();
	//		}
	//	}

	//	ImGui::Unindent();
	//}

	//if (ImGui::CollapsingHeader("Lights"))
	//{
	//	ImGui::Indent();

	//	for (size_t i = 0; i < lights.size(); i++)
	//	{

	//		if (ImGui::CollapsingHeader(lights[i].data()))
	//		{
	//			ImGui::Indent();

	//			adlVec3 light_position = spawn_transform_.o;
	//			adlVec3 light_rotation = spawn_transform_.rot;
	//			adlVec3 light_scale = spawn_transform_.scale;

	//			if (ImGui::CollapsingHeader("Transform"))
	//			{
	//				ImGui::Indent();

	//				if (ImGui::CollapsingHeader("Position"))
	//				{
	//					ImGui::Text("Position(x,y,z)");

	//					std::string label = lights[i] + " Pos";

	//					float lightPos[3] = { light_position.x, light_position.y, light_position.z };
	//					ImGui::InputFloat3(label.data(), &lightPos[0], 2);
	//					light_position = adlVec3(lightPos[0], lightPos[1], lightPos[2]);
	//				}
	//				if (ImGui::CollapsingHeader("Rotation"))
	//				{
	//					ImGui::Text("Rotation(x,y,z)");

	//					std::string label = lights[i] + " Rot";

	//					float lightRot[3] = { adlMath::rad_to_deg(light_rotation.x), adlMath::rad_to_deg(light_rotation.y), adlMath::rad_to_deg(light_rotation.z) };
	//					ImGui::InputFloat3(label.data(), &lightRot[0], 2);
	//					light_rotation = adlVec3(adlMath::deg_to_rad(lightRot[0]), adlMath::deg_to_rad(lightRot[1]), adlMath::deg_to_rad(lightRot[2]));
	//				}
	//				if (ImGui::CollapsingHeader("Scale"))
	//				{
	//					ImGui::Text("Scale(x,y,z)");

	//					std::string label = lights[i] + " Scale";

	//					float lightScale[3] = { light_scale.x, light_scale.y, light_scale.z };
	//					ImGui::InputFloat3(label.data(), &lightScale[0], 2);
	//					light_scale = adlVec3(lightScale[0], lightScale[1], lightScale[2]);
	//				}

	//				spawn_transform_.o = light_position;
	//				spawn_transform_.rot = light_rotation;
	//				spawn_transform_.scale = light_scale;

	//				ImGui::Unindent();
	//			}

	//			std::string button_label = "Spawn " + lights[i] + " light";


	//			if (ImGui::Button(button_label.data()))
	//			{
	//				ImGui::Indent();

	//				//scene_manager->spawn_light(lights[i].data(), spawn_transform_.o, spawn_transform_.rot, spawn_transform_.scale);

	//				is_visible_ = false;
	//				ImGui::Unindent();
	//			}

	//			ImGui::Unindent();
	//		}
	//	}

	//	ImGui::Unindent();
	//}

	//ImGui::End();
}

bool adlSpawn_editor::get_visible()
{
	return is_visible_;
}

