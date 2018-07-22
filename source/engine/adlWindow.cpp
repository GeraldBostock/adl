#include "adlWindow.h"



adlWindow::adlWindow(const std::string& title, int width, int height)
	: title_(title), 
	  width_(width), 
	  height_(height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
}


adlWindow::~adlWindow()
{
	SDL_DestroyWindow(window_);
}
