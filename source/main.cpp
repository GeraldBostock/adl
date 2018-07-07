#define SDL_MAIN_HANDLED
#include "adlWindow.h"
#include "adl_debug/adlAssert.h"
#include "adl_debug/adlLogger.h"

#include <iostream>
#include <stdio.h>

#ifdef ADL_TARGET_SYSTEM_UNIX
	#warning "C Preprocessor got here!"
#endif

int main(int argc, char* args[])
{

	(void)argc;
	(void)args;
	adlLogger::log_info("Starting adl", true);
	adlLogger::log_error("errrorororoororr", true);

	adlWindow window("Default Window", 1280, 720);

	while (1)
	{
		
	}

	return 0;
}
