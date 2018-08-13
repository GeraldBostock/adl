#include "adlWindow.h"

#include "adl_debug\adlLogger.h"

adlWindow::adlWindow(const std::string& title, int width, int height)
	: title_(title), 
	  width_(width), 
	  height_(height)
{
	adlLogger* adl_logger = &adlLogger::get();
#ifdef USE_SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		adl_logger->log_error("SDL failed to initialize: " + std::string(SDL_GetError()));
	}
	else
	{
		/*
		 * Set GL attributes.
		 * Assigns 8 bits for each rgba component
		 * Enables double buffering
		 */
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);

		/*
		 * Creates the window and tells SDL that the window will be used for drawing OpenGL stuff
		 */
		window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
		if (window_ == NULL)
		{
			adl_logger->log_error("Failed to create window: " + std::string(SDL_GetError()));
		}
		else
		{
			g_context_ = SDL_GL_CreateContext(window_);

			if (glewInit() != GLEW_OK)
			{
				adl_logger->log_error("Failed to initialize GLEW");
			}
		}
	}

	closed_ = false;
#endif // USE_SDL
}


adlWindow::~adlWindow()
{
	if (!closed_)
	{
		SDL_DestroyWindow(window_);
		SDL_Quit();
	}
}

void adlWindow::swap_buffers()
{
#ifdef USE_SDL
	SDL_GL_SwapWindow(window_);
#endif // USE_SDL
}

void adlWindow::close_window()
{
#ifdef USE_SDL
	SDL_GL_DeleteContext(g_context_);

	SDL_DestroyWindow(window_);
	window_ = NULL;

	SDL_Quit();

	closed_ = true;
#endif // USE_SDL
}
