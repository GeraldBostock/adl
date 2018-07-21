#include "adlInput.h"

unsigned char adlInput::keyboard_[] = { 0 };
unsigned char adlInput::prev_keyboard_[] = { 0 };

adlInput::Mouse_state adlInput::mouse_state_ = {};
adlInput::Mouse_state adlInput::prev_mouse_state_ = {};

adlInput::adlInput()
{
}


adlInput::~adlInput()
{
}

void adlInput::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
	}

	memcpy(adlInput::prev_keyboard_, adlInput::keyboard_, 323);
	memcpy(adlInput::keyboard_, SDL_GetKeyboardState(NULL), 323);

	Uint32 buttons;

	memcpy(&adlInput::prev_mouse_state_, &adlInput::mouse_state_, sizeof(adlInput::Mouse_state));
	buttons = SDL_GetMouseState(&adlInput::mouse_state_.x, &adlInput::mouse_state_.y);

	adlInput::mouse_state_.xDif = adlInput::mouse_state_.x - adlInput::prev_mouse_state_.x;
	adlInput::mouse_state_.yDif = adlInput::mouse_state_.y - adlInput::prev_mouse_state_.y;

	if (buttons & ADL_BUTTON(1))
		adlInput::mouse_state_.lmb = 1;
	else
		adlInput::mouse_state_.lmb = 0;

	if (buttons & ADL_BUTTON(3))
		adlInput::mouse_state_.rmb = 1;
	else
		adlInput::mouse_state_.rmb = 0;

	if (adlInput::mouse_state_.lmb == 0 && adlInput::prev_mouse_state_.lmb == 1)
		adlInput::mouse_state_.lmbr = 1;
	else
		adlInput::mouse_state_.lmbr = 0;

	if (adlInput::mouse_state_.rmb == 0 && adlInput::prev_mouse_state_.rmb == 1)
		adlInput::mouse_state_.rmbr = 1;
	else
		adlInput::mouse_state_.rmbr = 0;
}

bool adlInput::get_key(adl_keys key)
{
	return adlInput::keyboard_[key];
}

bool adlInput::get_key_down(adl_keys key)
{
	return adlInput::keyboard_[key] && !adlInput::prev_keyboard_[key];
}

bool adlInput::get_key_up(adl_keys key)
{
	return !adlInput::keyboard_[key] && adlInput::prev_keyboard_[key];
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