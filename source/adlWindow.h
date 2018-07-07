#ifndef adl_window_h__
#define adl_window_h__

#include <SDL2\SDL.h>
#include <string>

typedef SDL_Window* adlWindow_handle;

class adlWindow
{
public:
	adlWindow(const std::string& title, int width, int height);
	~adlWindow();

	int get_width() const
	{
		return width_;
	}
	int get_height() const
	{
		return height_;
	}

private:
	std::string title_;
	int width_;
	int height_;

	adlWindow_handle window_;
};

#endif // adl_window_h__

