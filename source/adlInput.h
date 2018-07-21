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
	static bool get_key(adl_keys key);
	static bool get_key_down(adl_keys key);
	static bool get_key_up(adl_keys key);

	static bool get_mouse_down(uint32 button);
	static bool get_mouse_up(uint32 button);

	static adlVec2_i32 get_mouse_pos();

	static int get_mouse_x_rel();
	static int get_mouse_y_rel();

	struct Mouse_state
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
	static unsigned char keyboard_[323];
	static unsigned char prev_keyboard_[323];

	static adlInput::Mouse_state mouse_state_;
	static adlInput::Mouse_state prev_mouse_state_;
};

#endif // adl_input_h__
