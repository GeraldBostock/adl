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
	adlInput* input = &adlInput::get();

	if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_s))
	{
		scene_saver_open_ = !scene_saver_open_;
	}

	if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_o))
	{
		scene_chooser_open_ = !scene_chooser_open_;
	}

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
		adlScene_manager* scene_manager = &adlScene_manager::get();

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
