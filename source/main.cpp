#define SDL_MAIN_HANDLED

#include "adlWindow.h" 
#include "adl_debug/adlAssert.h"
#include "adl_debug/adlLogger.h"
#include "adl_resource/adlResource_manager.h"
#include "adlInput.h"

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;

	adlResource_manager& adl_rm = adlResource_manager::get();

	adl_rm.get_mesh("box.obj");
	adl_rm.get_mesh("box.obj");
	adlWindow window("Default Window", 1280, 720);

	while (1)
	{
		adlInput::update();
	}

	return 0;
}
