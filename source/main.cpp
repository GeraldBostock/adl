#define SDL_MAIN_HANDLED
#include "adlWindow.h"
#include "adl_debug\adlAssert.h"
#include "adl_debug\adlLogger.h"

#include <iostream>

int main(int argc, char* args[])
{

	(void)argc;
	(void)args;
	adlLogger::log_info("Starting adl", true);

	adlWindow window("Default Window", 1280, 720);

	while (1)
	{
		
	}

	return 0;
}
