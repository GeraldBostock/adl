#ifndef adl_window_h__
#define adl_window_h__

#include "common.h"
#include "adlMemory.h"

#include <GL/glew.h>

#ifdef USE_SDL
	#define SDL_MAIN_HANDLED
	#include <SDL2/SDL.h>

	typedef SDL_Window* adlWindow_handle;
	typedef SDL_GLContext Graphics_context;
#endif // USE_SDL

#include <string>

class adlWindow
{
public:

	static adlWindow* get(const std::string& title, int width, int height)
	{
		if (instance_ == nullptr)
		{
			instance_ = ADL_NEW(adlWindow, title, width, height);
		}
		//static adlWindow* instance = ADL_NEW(adlWindow, title, width, height);
		//static adlWindow instance(title, width, height);
		return instance_;
	}
	static adlWindow* get()
	{
		if (instance_ == nullptr)
		{
			instance_ = ADL_NEW(adlWindow, "Default Window", 1280, 720);
		}
		//static adlWindow* instance;
		//static adlWindow instance;
		return instance_;
	}

	~adlWindow();

	int get_width() const
	{
		return width_;
	}
	int get_height() const
	{
		return height_;
	}

	void swap_buffers();
	void close_window();

	void set_mouse_visible(bool is_visible);

private:
	std::string title_;
	int width_;
	int height_;
	bool closed_;

	adlWindow_handle window_;
	Graphics_context g_context_;

	adlWindow(const std::string& title, int width, int height);
	adlWindow();

	static adlWindow* instance_;
};

#endif // adl_window_h__

