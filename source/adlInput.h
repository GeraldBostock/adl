#ifndef adl_input_h__
#define adl_input_h__

#include <string.h>
#include <stdio.h>
#include "adl_math/adlMath.h"
#include "sdl_definitions.h"

class adlInput
{
public:
	adlInput();
	virtual ~adlInput();

	static void update();
	static bool getKey(adlKeys key);
	static bool getKeyDown(adlKeys key);
	static bool getKeyUp(adlKeys key);

	static bool getMouseDown(Uint32 button);
	static bool getMouseUp(Uint32 button);

	static adlVec2_i32 getMousePos();

	static int getMouseXRel();
	static int getMouseYRel();

	struct Mouse
	{
		int x;
		int y;
		int xDif;
		int yDif;
		int lmb;
		int rmb;
		int lmbr;
		int rmbr;
	};

private:
	static unsigned char m_keyboard[323];
	static unsigned char m_prevKeyboard[323];

	static adlInput::Mouse m_mouse;
	static adlInput::Mouse m_prevMouse;
};

#endif // adl_input_h__
