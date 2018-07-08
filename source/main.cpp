#define SDL_MAIN_HANDLED
#include "adlWindow.h"
#include "adl_debug/adlAssert.h"
#include "adl_debug/adlLogger.h"
#include "adl_resource\adlResource_manager.h"

int main(int argc, char* args[])
{

	(void)argc;
	(void)args;
#ifdef ADL_TARGET_SYSTEM_WINDOWS
	adlLogger::log_info("Starting adl on Windows", true);
#elif defined ADL_TARGET_SYSTEM_UNIX
	adlLogger::log_info("Starting adl on Unix", true);
#endif

	adlResource_manager& adl_rm = adlResource_manager::get();

	adl_rm.get_mesh("box.obj");
	adl_rm.get_mesh("box.obj");
	adlWindow window("Default Window", 1280, 720);

	while (1)
	{
		
	}

	return 0;
}
