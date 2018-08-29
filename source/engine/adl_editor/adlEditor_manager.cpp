#include "adlEditor_manager.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adlWindow.h"
#include "engine/adlMemory.h"
#include "engine/adlScene_manager.h"

adlEditor_manager::adlEditor_manager()
	: light_editor_open_(false),
	  actor_editor_open_(false),
	  main_editor_open_(false),
	  light_editor_(nullptr),
	  actor_editor_(nullptr)
{
	light_editor_ = ADL_NEW(adlLight_editor);
	actor_editor_ = ADL_NEW(adlActor_editor);
}

void adlEditor_manager::update()
{
	adlInput* input = &adlInput::get();
	if (input->get_key(adl_key_left_ctrl) && input->get_key_up(adl_key_z))
	{
		main_editor_open_ = !main_editor_open_;

		adlWindow* window = adlWindow::get();
		if (main_editor_open_)
		{
			window->set_mouse_visible(true);
		}
		else
		{
			window->set_mouse_visible(false);
			light_editor_open_ = false;
			actor_editor_open_ = false;
		}
	}

	if (main_editor_open_)
	{
		ImGui::Begin("ADL Editor");
		if (ImGui::Button("Light Editor"))
		{
			light_editor_open_ = true;
		}
		if (ImGui::Button("Actor Editor"))
		{
			actor_editor_open_ = true;
		}
		ImGui::End();

		adlScene_manager* scene_manager = &adlScene_manager::get();
		if (light_editor_open_)
		{
			light_editor_->update(scene_manager->get_sun(), scene_manager->get_all_point_lights());
		}
		if (actor_editor_open_)
		{
			actor_editor_->update(scene_manager->get_all_actors());
		}
	}
}
