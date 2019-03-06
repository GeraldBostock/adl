#include "adlRoot.h"

#include "adl_debug/imgui/imgui.h"
#include "adl_debug/imgui/imgui_impl_sdl.h"
#include "adl_debug/imgui/imgui_impl_opengl3.h"

adlRoot::adlRoot()
	: is_running_(false)
{
}

adlRoot::~adlRoot()
{
	ADL_DELETE(fps_manager_);
	ADL_DELETE(camera);
	ADL_DELETE(physics_);

#ifdef _DEBUG
	ADL_DELETE(terrain_debugger);
#endif // _DEBUG

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void adlRoot::init_window(const std::string& title, int width, int height)
{
	adl_window = adlWindow::get(title, width, height);
}

void adlRoot::run()
{
	adl_input->update();
	if (!adl_input->has_focus())
	{
		return;
	}
	adl_renderer->prepare();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(adl_window->get_window());
	ImGui::NewFrame();

	if (adl_input->close_button_pressed())
	{
		is_running_ = false;
		return;
	}

	float dt = fps_manager_->enforce_fps();

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key(adl_key_left_alt) && adl_input->get_key_up(adl_key_w))
	{
		adl_renderer->toggle_wire_frame_mode();
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_up(adl_key_v))
	{
		adl_window->set_mouse_visible(true);
	}

	if (!update(dt))
	{
		is_running_ = false;
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_z))
	{
		rendering_bounding_boxes_ = !rendering_bounding_boxes_;
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_p))
	{
		rendering_physics_diagnostics_ = !rendering_physics_diagnostics_;
	}

	if (rendering_physics_diagnostics_)
	{
		physics_->render_diagnostics();
	}

	if (rendering_bounding_boxes_)
	{
		debug_renderer->render_bounding_boxes();
	}

	mouse_picker->update(adl_renderer->get_projection_matrix(), adl_scene_manager->get_camera()->get_view_matrix());

	adl_scene_manager->update(dt);
	adl_scene_manager->render();

	//physics_->sync_physics_to_rendering();
	physics_->update(dt);
	physics_->sync_scene();

	terrain_debugger->update();

	debug_renderer->render();
	debug_renderer->clear_render_queue();

#ifdef _DEBUG
	adl_editor->update();

	float fps = fps_manager_->get_fps();
	std::string fps_string = std::to_string(fps);
	fps_string = fps_string.substr(0, fps_string.size() - 4);

	adlFont_shared_ptr arial = adl_rm->get_font("arial");
	adl_renderer->render_text("FPS: " + fps_string, arial, 0.89f * adl_window->get_width(), 0.95f * adl_window->get_height(), 0.5f, adlColor::YELLOW);
#endif // _DEBUG

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	adl_window->swap_buffers();
}

void adlRoot::start()
{
	is_running_ = true;
	game_thread();
}

void adlRoot::game_thread()
{
	adl_rm				= &adlResource_manager::get();
	adl_renderer		= &adlRender_manager::get();
	adl_input			= &adlInput::get();
	adl_logger			= &adlLogger::get();
	adl_scene_manager	= &adlScene_manager::get();
	mouse_picker		= &adlMouse_picker::get();
	debug_renderer		= &adlDebug_renderer::get();
#ifdef _DEBUG
	adl_editor			= &adlEditor_manager::get();
	terrain_debugger	= ADL_NEW(adlTerrain_debugger);
#endif // _DEBUG
	camera				= ADL_NEW(adlCamera);
	physics_			= ADL_NEW(adlBullet_physics);
	physics_->initialize();

	adl_scene_manager->set_physics(physics_);

	//adl_scene_manager->set_camera(camera);
	adlMat4 projection_matrix = projection_matrix.create_projection_matrix(adl_window->get_width(), adl_window->get_height(), adlMath::deg_to_rad(45), 0.1f, 1000.0f);
	adl_renderer->set_projection(projection_matrix);

	if (!init())
	{
		is_running_ = false;
	}

	fps_manager_ = ADL_NEW(adlFPS_manager, 120, 0.5f);

	while (is_running_)
	{
		run();
	}

#ifdef _DEBUG
	adl_editor->clean_up();
#endif //_DEBUG
	adl_window->close_window();
}