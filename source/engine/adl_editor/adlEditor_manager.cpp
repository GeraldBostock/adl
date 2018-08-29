#include "adlEditor_manager.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adlWindow.h"
#include "engine/adlMemory.h"
#include "engine/adlScene_manager.h"
#include "engine/adlShared_types.h"

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

void adlEditor_manager::MainMenu()
{
	adlScene_manager* scene_manager = &adlScene_manager::get();
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("adl Editors"))
		{
			ImGui::Checkbox("Entity Editor", &entity_editor_open_);
			ImGui::Checkbox("Actor Editor", &actor_editor_open_);
			ImGui::Checkbox("Light Editor", &light_editor_open_);
			ImGui::Checkbox("Help", &help_open_);

			if (ImGui::MenuItem("Close All Editors", "CTRL+Q"))
			{
				entity_editor_open_ = false;
				actor_editor_open_ = false;
				light_editor_open_ = false;
				help_open_ = false;
				show_demo_window = false;
			}

			ImGui::EndMenu();

		}
		ImGui::Text("|");

		if (ImGui::BeginMenu("Game"))
		{
			if (ImGui::MenuItem("Spawn", "SHIFT+A"))
			{
				std::cout << "Spawned!" << std::endl;
			}
			if (ImGui::MenuItem("Save", "CTRL+S")) { std::cout << "Saved!" << std::endl; }

			if (ImGui::MenuItem("Quit", "ESC")) {}

			ImGui::EndMenu();
		}		

		ImGui::Text("|");

		if (ImGui::BeginMenu("Cameras"))
		{
			if (ImGui::MenuItem("FPS")) { std::cout << "FPS" << std::endl; }
			if (ImGui::MenuItem("RTS")) { std::cout << "RTS" << std::endl; }
			if (ImGui::MenuItem("GOD")) { std::cout << "GOD" << std::endl; }
			if (ImGui::MenuItem("Custom")) { std::cout << "Custom" << std::endl; }

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void adlEditor_manager::update()
{
	adlInput* input = &adlInput::get();
	if (input->get_key(adl_key_left_ctrl) && input->get_key_up(adl_key_left_shift))
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
			entity_editor_open_ = false;
			actor_editor_open_ = false;
			light_editor_open_ = false;
			help_open_ = false;		
			show_demo_window = false;
		}
	}

	if (main_editor_open_)
	{
		MainMenu();

		adlScene_manager* scene_manager = &adlScene_manager::get();
		if (entity_editor_open_)
		{
			entity_editor_->update(scene_manager->get_all_entities());
		}
		if (actor_editor_open_)
		{
			actor_editor_->update(scene_manager->get_all_actors());
		}
		if (light_editor_open_)
		{
			light_editor_->update(scene_manager->get_sun(), scene_manager->get_all_point_lights());
		}
		if (help_open_)
		{
			ImGui::Begin("Help");
			ImGui::Text("Close/Open Editor: 'CTRL(or CMD)+Shift'");
			ImGui::Text("Show/Hide Sub Editors:  'adl Editors->Toggle Checkbox'");

			if (ImGui::CollapsingHeader("Extras"))
			{
				ImGui::Indent();
				ImGui::Checkbox("Demo Window", &show_demo_window);

				if (show_demo_window)
					ImGui::ShowDemoWindow(&show_demo_window);
				ImGui::Unindent();
			}

			ImGui::End();

		}
	}
}
