#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <iostream>

#include "adlWindow.h" 
#include "adl_debug/adlAssert.h"
#include "adl_debug/adlLogger.h"
#include "adl_resource/adlResource_manager.h"
#include "adl_math/adlMath.h"
#include "adlInput.h"
#include "adl_resource/adlModel.h"

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;

	adlResource_manager& adl_rm = adlResource_manager::get();

	adlWindow window("Default Window", 1280, 720);

	adlModel_shared_ptr model = adl_rm.get_model("box");
	adlModel_shared_ptr other_model = adl_rm.get_model("box");
	adlModel_shared_ptr rifle_model = adl_rm.get_model("rifle");
	adlModel_shared_ptr segment_model = adl_rm.get_model("segment");
	adlModel_shared_ptr duck_model = adl_rm.get_model("duck");

	while (1)
	{
		adlInput::update();
	}

	return 0;
}
