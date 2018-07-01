#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	while(true)
	{
	}
	
	SDL_Quit();

	return 0;
}
