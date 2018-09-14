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
		adlResource_manager* adl_rm = &adlResource_manager::get();
		adlScene_manager* scene_manager = &adlScene_manager::get();

		adlScene_shared_ptr active_scene = scene_manager->get_active_scene();
		std::string serialized_scene = adl_rm->serialize_scene(active_scene);

		std::ofstream output_file("res/scenes/test.json");
		output_file << serialized_scene;
		output_file.close();


	}
}
