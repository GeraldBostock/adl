#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <iostream>
#include "adlRoot.h"

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;

	adlRoot adlroot;
	adlroot.run();

	return 0;
}
