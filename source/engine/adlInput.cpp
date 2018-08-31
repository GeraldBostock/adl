#include "adlInput.h"

#include <iostream>
#include "adl_debug/imgui/imgui.h"
#include "adl_debug/imgui/imgui_impl_sdl.h"
#include "adl_debug/imgui/imgui_impl_opengl3.h"

adlInput::adlInput()
{
}

void adlInput::update()
{
	mouse_state_.xDif = 0;
	mouse_state_.yDif = 0;

	memcpy(prev_keyboard_, keyboard_, 323);
	memcpy(keyboard_, SDL_GetKeyboardState(NULL), 323);

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			close_button_ = true;
		}
		else
		{
			close_button_ = false;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			mouse_state_.xDif = e.motion.xrel;
			mouse_state_.yDif = e.motion.yrel;
		}

		switch (e.key.keysym.sym)
		{
		case SDLK_QUOTEDBL:
			keyboard_[adl_key_quotedbl] = true;
			break;
		case SDLK_GREATER:
			keyboard_[adl_key_greater] = true;
			break;
		case SDLK_LESS:
			keyboard_[adl_key_less] = true;
			break;
		default:
			for (int i = 320; i < 323; i++)
			{
				keyboard_[i] = false;
			}
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	Uint32 buttons;

	memcpy(&prev_mouse_state_, &mouse_state_, sizeof(Mouse_state));
	buttons = SDL_GetMouseState(&mouse_state_.x, &mouse_state_.y);

	if (buttons & ADL_BUTTON(1))
	{
		mouse_state_.lmb = 1;
	}
	else
	{
		mouse_state_.lmb = 0;
	}

	if (buttons & ADL_BUTTON(3))
	{
		mouse_state_.rmb = 1;
	}
	else
	{
		mouse_state_.rmb = 0;
	}

	if (mouse_state_.lmb == 0 && prev_mouse_state_.lmb == 1)
	{
		mouse_state_.lmbr = 1;
	}
	else
	{
		mouse_state_.lmbr = 0;
	}

	if (mouse_state_.rmb == 0 && prev_mouse_state_.rmb == 1)
	{
		mouse_state_.rmbr = 1;
	}
	else
	{
		mouse_state_.rmbr = 0;
	}
}

bool adlInput::get_key(adl_keys key)
{
	return keyboard_[key];
}

bool adlInput::get_key_down(adl_keys key)
{
	return keyboard_[key] && !prev_keyboard_[key];
}

bool adlInput::get_key_up(adl_keys key)
{
	return !keyboard_[key] && prev_keyboard_[key];
}

bool adlInput::get_mouse_down(uint32 button)
{
	switch (button)
	{
	case ADL_BUTTON_LEFT:
		return mouse_state_.lmb && !prev_mouse_state_.lmb;
		break;
	case ADL_BUTTON_RIGHT:
		return mouse_state_.rmb && !prev_mouse_state_.rmb;
		break;
	}

	return false;
}

bool adlInput::get_mouse_up(uint32 button)
{
	switch (button)
	{
	case ADL_BUTTON_LEFT:
		return !mouse_state_.lmb && prev_mouse_state_.lmb;
		break;
	case ADL_BUTTON_RIGHT:
		return !mouse_state_.rmb && prev_mouse_state_.rmb;
		break;
	}

	return false;
}

adlVec2_i32 adlInput::get_mouse_pos()
{
	return adlVec2_i32{ mouse_state_.x, mouse_state_.y };
}

int adlInput::get_mouse_x_rel()
{
	return mouse_state_.xDif;
}

int adlInput::get_mouse_y_rel()
{
	return mouse_state_.yDif;
}

bool adlInput::close_button_pressed()
{
	return close_button_;
}