#include "adlRoot.h"

adlRoot::adlRoot()
{
	is_running_ = false;
}

adlRoot::~adlRoot()
{
	ADL_DELETE(fps_manager_);
	ADL_DELETE(camera);
}

void adlRoot::init_window(const std::string& title, int width, int height)
{
	adl_window = adlWindow::get(title, width, height);
}

void adlRoot::run()
{
	adl_input->update();
	adl_renderer->prepare();

	if (adl_input->close_button_pressed())
	{
		is_running_ = false;
		return;
	}

	int64 dt = fps_manager_->enforce_fps();

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key(adl_key_left_alt) && adl_input->get_key_up(adl_key_w))
	{
		adl_renderer->toggle_wire_frame_mode();
	}

	camera->update(dt);
	if (!update(dt))
	{
		is_running_ = false;
	}

	adl_scene_manager->update(dt);
	adl_scene_manager->render();

	float fps = fps_manager_->get_fps();
	std::string fps_string = std::to_string(fps);
	fps_string = fps_string.substr(0, fps_string.size() - 4);

	adlFont_shared_ptr arial = adl_rm->get_font("arial");
	adl_renderer->render_text("FPS: " + fps_string, arial, 0.89f * adl_window->get_width(), 0.95f * adl_window->get_height(), 0.5f, adlColor::YELLOW);

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
	camera				= ADL_NEW(adlCamera);

	adl_renderer->set_camera(camera);
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

	adl_window->close_window();
}