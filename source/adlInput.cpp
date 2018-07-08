#include "adlInput.h"

unsigned char adlInput::m_keyboard[] = { 0 };
unsigned char adlInput::m_prevKeyboard[] = { 0 };

adlInput::Mouse adlInput::m_mouse = {};
adlInput::Mouse adlInput::m_prevMouse = {};

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

	memcpy(adlInput::m_prevKeyboard, adlInput::m_keyboard, 323);
	memcpy(adlInput::m_keyboard, SDL_GetKeyboardState(NULL), 323);

	Uint32 buttons;

	memcpy(&adlInput::m_prevMouse, &adlInput::m_mouse, sizeof(adlInput::Mouse));
	buttons = SDL_GetMouseState(&adlInput::m_mouse.x, &adlInput::m_mouse.y);

	adlInput::m_mouse.xDif = adlInput::m_mouse.x - adlInput::m_prevMouse.x;
	adlInput::m_mouse.yDif = adlInput::m_mouse.y - adlInput::m_prevMouse.y;

	if (buttons & ADL_BUTTON(1))
		adlInput::m_mouse.lmb = 1;
	else
		adlInput::m_mouse.lmb = 0;

	if (buttons & ADL_BUTTON(3))
		adlInput::m_mouse.rmb = 1;
	else
		adlInput::m_mouse.rmb = 0;

	if (adlInput::m_mouse.lmb == 0 && adlInput::m_prevMouse.lmb == 1)
		adlInput::m_mouse.lmbr = 1;
	else
		adlInput::m_mouse.lmbr = 0;

	if (adlInput::m_mouse.rmb == 0 && adlInput::m_prevMouse.rmb == 1)
		adlInput::m_mouse.rmbr = 1;
	else
		adlInput::m_mouse.rmbr = 0;
}

bool adlInput::getKey(adlKeys key)
{
	return adlInput::m_keyboard[key];
}

bool adlInput::getKeyDown(adlKeys key)
{
	return adlInput::m_keyboard[key] && !adlInput::m_prevKeyboard[key];
}

bool adlInput::getKeyUp(adlKeys key)
{
	return !adlInput::m_keyboard[key] && adlInput::m_prevKeyboard[key];
}

bool adlInput::getMouseDown(Uint32 button)
{
	switch (button)
	{
	case ADL_BUTTON_LEFT:
		return m_mouse.lmb && !m_prevMouse.lmb;
		break;
	case ADL_BUTTON_RIGHT:
		return m_mouse.rmb && m_prevMouse.rmb;
		break;
	}

	return false;
}

bool adlInput::getMouseUp(Uint32 button)
{
	switch (button)
	{
	case ADL_BUTTON_LEFT:
		return !m_mouse.lmb && m_prevMouse.lmb;
		break;
	case ADL_BUTTON_RIGHT:
		return !m_mouse.rmb && m_prevMouse.rmb;
		break;
	}

	return false;
}

adlVec2_i32 adlInput::getMousePos()
{
	return adlVec2_i32{ m_mouse.x, m_mouse.y };
}

int adlInput::getMouseXRel()
{
	return m_mouse.xDif;
}

int adlInput::getMouseYRel()
{
	return m_mouse.yDif;
}
