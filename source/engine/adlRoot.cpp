#include "adlRoot.h"

#include "adlMemory.h"
#include "adl_resource/adlResource_manager.h"
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
}

void adlRoot::init_window(const std::string& title, int width, int height)
{
	window_ = ADL_NEW(adlWindow, title, width, height);
}

void adlRoot::run()
{
	adl_input->update();

	double dt = fps_manager_->enforce_fps();

	if (!update(dt))
	{
		is_running_ = false;
	}
}

void adlRoot::start()
{
	is_running_ = true;
	game_thread();
}

void adlRoot::game_thread()
{
	if (!init())
	{
		is_running_ = false;
	}

	adl_rm = &adlResource_manager::get();
	adl_input = &adlInput::get();

	fps_manager_ = ADL_NEW(adlFPS_manager, 120, 1.0);

	while (is_running_)
	{
		run();
	}
}