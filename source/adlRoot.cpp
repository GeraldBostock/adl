#include "adlRoot.h"

#include "adlMemory.h"
#include "adl_resource/adlResource_manager.h"
#include "adlWindow.h"
#include "adl_debug/adlLogger.h"
#include "adlInput.h"
#include "adl_helper/adlFPS_manager.h"

adlRoot::adlRoot()
{
	window_ = ADL_NEW(adlWindow, "Default Window", 1280, 720);
}

adlRoot::~adlRoot()
{
	ADL_DELETE(window_);
	ADL_DELETE(fps_manager_);
}

void adlRoot::run()
{
	adlResource_manager& adl_rm = adlResource_manager::get();

	adlModel_shared_ptr model = adl_rm.get_model("box");
	adlModel_shared_ptr other_model = adl_rm.get_model("box");
	adlModel_shared_ptr rifle_model = adl_rm.get_model("rifle");
	adlModel_shared_ptr segment_model = adl_rm.get_model("segment");
	adlModel_shared_ptr duck_model = adl_rm.get_model("duck");

	adlTimer second_timer;
	second_timer.start();

	fps_manager_ = ADL_NEW(adlFPS_manager, 60, 1.0);
	while (1)
	{
		if (adlInput::get_key_up(adl_key_escape))
		{
			break;
		}
		adlInput::update();

		double dt = fps_manager_->enforce_fps();
	}
}