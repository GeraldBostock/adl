#include "adlEditor_manager.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adlWindow.h"
#include "engine/adlMemory.h"
#include "engine/adlScene_manager.h"
#include "engine/adlShared_types.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_entities/adlEntity_factory.h"

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
				show_demo_window_ = false;

				spawner_editor_open_ = false;
			}

			ImGui::EndMenu();

		}
		ImGui::Text("|");

		if (ImGui::BeginMenu("Game"))
		{
			if (ImGui::MenuItem("Spawn", "SHIFT+A"))
			{
				adlEntity_factory* factory = &adlEntity_factory::get();
				const std::vector<std::string> actors = factory->get_all_registered_actors();
				const std::vector<std::string> lights = factory->get_all_registered_lights();
				for (auto key : actors)
				{
					std::cout << key << std::endl;
				}

				for (auto key : lights)
				{
					std::cout << key << std::endl;
				}

				adlScene_manager* scene_manager = &adlScene_manager::get();
				scene_manager->spawn_light("adlPoint_light");
				scene_manager->spawn_actor("Test_actor");

				spawner_editor_open_ = false;
			}
			if (ImGui::MenuItem("Save", "CTRL+S")) { std::cout << "Saved!" << std::endl; }

			if (ImGui::MenuItem("Quit", "ESC")) {}

			ImGui::EndMenu();
		}		

		ImGui::Text("|");

		if (ImGui::BeginMenu("Cameras"))
		{
			adlScene_manager* scene_manager = &adlScene_manager::get();
			adlCamera* c = scene_manager->getCamera();

			if (ImGui::MenuItem("GOD")) { c->set_camera_type(ct_god_mode); }
			if (ImGui::MenuItem("RTS")) { c->set_camera_type(ct_rts); }
			if (ImGui::MenuItem("FPS")) { c->set_camera_type(ct_fps); }
			if (ImGui::MenuItem("Custom")) { c->set_camera_type(ct_custom); }

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void adlEditor_manager::update()
{
	adlInput* input = &adlInput::get();
	adlScene_manager* scene_manager = &adlScene_manager::get();
	if (input->get_key(adl_key_quotedbl) || (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_left_shift)))
	{
		main_editor_open_ = !main_editor_open_;

		adlWindow* window = adlWindow::get();
		if (main_editor_open_)
		{
			window->set_mouse_visible(true);
			scene_manager->getCamera()->toggle_active();
		}
		else
		{
			window->set_mouse_visible(false);
			entity_editor_open_ = false;
			actor_editor_open_ = false;
			light_editor_open_ = false;
			help_open_ = false;		
			show_demo_window_ = false;

			spawner_editor_open_ = false;

			scene_manager->getCamera()->toggle_active();
		}
	}

	if (main_editor_open_)
	{
		MainMenu();


		// adlEditor Shortcuts
		if (input->get_key(adl_key_left_shift) && input->get_key_down(adl_key_a))
		{
			spawner_editor_open_ = true;
		}

		// adlEditors
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
			ImGui::Text("Game Menu:  'Game->...'");
			ImGui::Text("Change Cameras:  'Cameras-><CamType>'");

			if (ImGui::CollapsingHeader("Extras"))
			{
				ImGui::Indent();
				ImGui::Checkbox("Demo Window", &show_demo_window_);

				if (show_demo_window_)
					ImGui::ShowDemoWindow(&show_demo_window_);
				ImGui::Unindent();
			}

			ImGui::End();
		}
		if (spawner_editor_open_)
		{
			adlEntity_factory* factory = &adlEntity_factory::get();
			const std::vector<std::string> actors = factory->get_all_registered_actors();
			const std::vector<std::string> lights = factory->get_all_registered_lights();

			ImGui::Begin("Spawn Editor");

			if (ImGui::CollapsingHeader("Actors"))
			{
				for (size_t i = 0; i < actors.size(); i++)
				{
					if (ImGui::Button(actors[i].data()))
					{
						ImGui::Indent();

						scene_manager->spawn_actor(actors[i].data());

						spawner_editor_open_ = false;
						ImGui::Unindent();
					}
				}
			}

			if (ImGui::CollapsingHeader("Lights"))
			{
				for (size_t i = 0; i < lights.size(); i++)
				{
					if (ImGui::Button(lights[i].data()))
					{
						ImGui::Indent();

						scene_manager->spawn_light(lights[i].data());

						spawner_editor_open_ = false;
						ImGui::Unindent();
					}
				}
			}

			ImGui::End();
		}
	}
}

void adlEditor_manager::clean_up()
{
	ADL_DELETE(entity_editor_);
	ADL_DELETE(actor_editor_);
	ADL_DELETE(light_editor_);
}
