#include "adlRoot.h"

#include "adlMemory.h"
#include "adl_resource/adlResource_manager.h"
#include "adl_renderer/adlRender_manager.h"
#include "adlWindow.h"
#include "adl_debug/adlLogger.h"
#include "adlInput.h"
#include "adl_helper/adlFPS_manager.h"

adlRoot::adlRoot()
{
	is_running_ = false;
}

adlRoot::~adlRoot()
{
	ADL_DELETE(window_);
	ADL_DELETE(fps_manager_);
	ADL_DELETE(camera);
}

void adlRoot::init_window(const std::string& title, int width, int height)
{
	window_ = ADL_NEW(adlWindow, title, width, height);
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
		adl_renderer->set_wire_frame_mode();
	}

	camera->update(dt);
	if (!update(dt))
	{
		is_running_ = false;
	}

	window_->swap_buffers();
}

void adlRoot::start()
{
	is_running_ = true;
	game_thread();
}

void adlRoot::game_thread()
{
	adl_rm = &adlResource_manager::get();
	adl_renderer = &adlRender_manager::get();
	adl_input = &adlInput::get();
	adl_logger = &adlLogger::get();
	camera = ADL_NEW(adlCamera);

	adl_renderer->set_camera(camera);

	if (!init())
	{
		is_running_ = false;
	}

	fps_manager_ = ADL_NEW(adlFPS_manager, 120, 2.5);

	while (is_running_)
	{
		run();
	}

	window_->close_window();
}