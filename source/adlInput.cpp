#include "adlInput.h"

unsigned char adlInput::keyboard_[] = { 0 };
unsigned char adlInput::prev_keyboard_[] = { 0 };

adlInput::Mouse adlInput::mouse_ = {};
adlInput::Mouse adlInput::prev_mouse_ = {};

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

	memcpy(&adlInput::prev_mouse_, &adlInput::mouse_, sizeof(adlInput::Mouse));
	buttons = SDL_GetMouseState(&adlInput::mouse_.x, &adlInput::mouse_.y);

	adlInput::mouse_.xDif = adlInput::mouse_.x - adlInput::prev_mouse_.x;
	adlInput::mouse_.yDif = adlInput::mouse_.y - adlInput::prev_mouse_.y;

	if (buttons & ADL_BUTTON(1))
		adlInput::mouse_.lmb = 1;
	else
		adlInput::mouse_.lmb = 0;

	if (buttons & ADL_BUTTON(3))
		adlInput::mouse_.rmb = 1;
	else
		adlInput::mouse_.rmb = 0;

	if (adlInput::mouse_.lmb == 0 && adlInput::prev_mouse_.lmb == 1)
		adlInput::mouse_.lmbr = 1;
	else
		adlInput::mouse_.lmbr = 0;

	if (adlInput::mouse_.rmb == 0 && adlInput::prev_mouse_.rmb == 1)
		adlInput::mouse_.rmbr = 1;
	else
		adlInput::mouse_.rmbr = 0;
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
		return mouse_.lmb && !prev_mouse_.lmb;
		break;
	case ADL_BUTTON_RIGHT:
		return mouse_.rmb && prev_mouse_.rmb;
		break;
	}

	return false;
}

bool adlInput::get_mouse_up(uint32 button)
{
	switch (button)
	{
	case ADL_BUTTON_LEFT:
		return !mouse_.lmb && prev_mouse_.lmb;
		break;
	case ADL_BUTTON_RIGHT:
		return !mouse_.rmb && prev_mouse_.rmb;
		break;
	}

	return false;
}

adlVec2_i32 adlInput::get_mouse_pos()
{
	return adlVec2_i32{ mouse_.x, mouse_.y };
}

int adlInput::get_mouse_x_rel()
{
	return mouse_.xDif;
}

int adlInput::get_mouse_y_rel()
{
	return mouse_.yDif;
}