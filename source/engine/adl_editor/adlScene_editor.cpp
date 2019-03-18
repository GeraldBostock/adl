#include "adlScene_editor.h"

#include "engine/adlInput.h"
#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlScene_manager.h"

#include <fstream>

adlScene_editor::adlScene_editor()
{
}


adlScene_editor::~adlScene_editor()
{
}

void adlScene_editor::update()
{
	adlScene_manager* scene_manager = &adlScene_manager::get();
	adlInput* input = &adlInput::get();

	if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_s))
	{
		scene_saver_open_ = !scene_saver_open_;
	}

	if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_o))
	{
		scene_chooser_open_ = !scene_chooser_open_;
	}

	ImGui::Begin("Scene Editor");
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Indent();
		adlCamera* camera = scene_manager->get_camera();
		if (ImGui::CollapsingHeader("Position"))
		{
			adlVec3 position = camera->get_position();
			ImGui::Text("Position(x,y,z)");

			std::string label = "##Position";

			float camera_position[3] = { position.x, position.y, position.z };
			ImGui::InputFloat3(label.data(), &camera_position[0], 2);
			camera->set_position(adlVec3(camera_position[0], camera_position[1], camera_position[2]));
		}

		if (ImGui::CollapsingHeader("Rotation"))
		{
			float pitch = camera->get_pitch();
			float yaw = camera->get_yaw();
			float roll = camera->get_roll();
			ImGui::Text("Rotation(pitch, yaw, roll)");

			std::string label = "##Rotation";

			float camera_rotation[3] = { pitch, yaw, roll };
			ImGui::InputFloat3(label.data(), &camera_rotation[0], 2);
			camera->set_pitch(camera_rotation[0]);
			camera->set_yaw(camera_rotation[1]);
			camera->set_roll(camera_rotation[2]);
		}
		ImGui::Unindent();
	}
	ImGui::End();

	if (scene_saver_open_)
	{
		ImGui::Begin("Save Scene");

		static char scene_name[20] = {};
		ImGui::InputText("(max 20 char)", scene_name, sizeof(scene_name));
		if (ImGui::Button("Save"))
		{
			save_scene(scene_name);
		}

		ImGui::End();
	}

	if (scene_chooser_open_)
	{
		adlResource_manager* adl_rm = &adlResource_manager::get();

		const std::vector<std::string>& scene_names = adl_rm->get_all_scene_names();

		ImGui::Begin("Scenes");

		if (ImGui::CollapsingHeader("Scenes"))
		{
			for (auto scene_name : scene_names)
			{
				if (ImGui::Button(scene_name.c_str()))
				{
					adlScene_shared_ptr scene = adl_rm->get_scene(scene_name);
					scene_manager->set_active_scene(scene);
				}
			}
		}

		ImGui::End();
	}
}

void adlScene_editor::save_scene(const char* scene_name)
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlScene_manager* scene_manager = &adlScene_manager::get();

	adlScene_shared_ptr active_scene = scene_manager->get_active_scene();
	std::string serialized_scene = adl_rm->serialize_scene(active_scene);

	std::string scn_name(scene_name);

	std::ofstream output_file("res/scenes/" + scn_name + ".json");
	output_file << serialized_scene;
	output_file.close();
}
