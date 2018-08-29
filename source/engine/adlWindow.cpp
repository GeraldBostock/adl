#include "adlWindow.h"

#include "engine/adl_debug/adlLogger.h"

#include "adl_debug/imgui/imgui.h"
#include "adl_debug/imgui/imgui_impl_sdl.h"
#include "adl_debug/imgui/imgui_impl_opengl3.h"

adlWindow* adlWindow::instance_ = nullptr;

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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_DisplayMode current;
		SDL_GetCurrentDisplayMode(0, &current);

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(window_, g_context_);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGui::StyleColorsDark();

	is_fullscreen_ = false;
	closed_ = false;
#endif // USE_SDL
}


adlWindow::~adlWindow()
{
	if (!closed_)
	{
		SDL_GL_DeleteContext(g_context_);
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

void adlWindow::set_mouse_visible(bool is_visible)
{
	if (is_visible)
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}

void adlWindow::set_fullscreen(bool is_fullscreen)
{
	if (!is_fullscreen_ && is_fullscreen)
	{
		SDL_SetWindowFullscreen(window_, true);

		SDL_DisplayMode dm;

		if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
		{
		}

		fullscreen_width_ = dm.w;
		fullscreen_height_ = dm.h;
	}
	else if(is_fullscreen_ && !is_fullscreen)
	{
		SDL_SetWindowFullscreen(window_, false);
		SDL_SetWindowSize(window_, width_, height_);
	}

	is_fullscreen_ = is_fullscreen;
}

void adlWindow::toggle_fullscreen()
{
	if (is_fullscreen_)
	{
		set_fullscreen(false);
	}
	else
	{
		set_fullscreen(true);
	}
}

adlWindow_handle adlWindow::get_window()
{
	return window_;
}
 
