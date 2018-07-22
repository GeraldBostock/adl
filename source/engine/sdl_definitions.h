#ifndef sdl_definitions_h__
#define sdl_definitions_h__

#include <SDL2/SDL.h>

#define ADL_BUTTON SDL_BUTTON
#define ADL_BUTTON_LEFT SDL_BUTTON_LEFT
#define ADL_BUTTON_RIGHT SDL_BUTTON_RIGHT

enum adl_keys
{
	adl_key_0 = SDL_SCANCODE_0,
	adl_key_1 = SDL_SCANCODE_1,
	adl_key_2 = SDL_SCANCODE_2,
	adl_key_3 = SDL_SCANCODE_3,
	adl_key_4 = SDL_SCANCODE_4,
	adl_key_5 = SDL_SCANCODE_5,
	adl_key_6 = SDL_SCANCODE_6,
	adl_key_7 = SDL_SCANCODE_7,
	adl_key_8 = SDL_SCANCODE_8,
	adl_key_9 = SDL_SCANCODE_9,

	adl_key_a = SDL_SCANCODE_A,
	adl_key_b = SDL_SCANCODE_B,
	adl_key_c = SDL_SCANCODE_C,
	adl_key_d = SDL_SCANCODE_D,
	adl_key_e = SDL_SCANCODE_E,
	adl_key_f = SDL_SCANCODE_F,
	adl_key_g = SDL_SCANCODE_G,
	adl_key_h = SDL_SCANCODE_H,
	adl_key_i = SDL_SCANCODE_I,
	adl_key_j = SDL_SCANCODE_J,
	adl_key_k = SDL_SCANCODE_K,
	adl_key_l = SDL_SCANCODE_L,
	adl_key_m = SDL_SCANCODE_M,
	adl_key_n = SDL_SCANCODE_N,
	adl_key_o = SDL_SCANCODE_O,
	adl_key_p = SDL_SCANCODE_P,
	adl_key_q = SDL_SCANCODE_Q,
	adl_key_r = SDL_SCANCODE_R,
	adl_key_s = SDL_SCANCODE_S,
	adl_key_t = SDL_SCANCODE_T,
	adl_key_u = SDL_SCANCODE_U,
	adl_key_v = SDL_SCANCODE_V,
	adl_key_w = SDL_SCANCODE_W,
	adl_key_x = SDL_SCANCODE_X,
	adl_key_y = SDL_SCANCODE_Y,
	adl_key_z = SDL_SCANCODE_Z,

	adl_key_escape = SDL_SCANCODE_ESCAPE,

	adl_key_left_ctrl = SDL_SCANCODE_LCTRL,
	adl_key_right_ctrl = SDL_SCANCODE_RCTRL,

	adl_key_left_shift = SDL_SCANCODE_LSHIFT,
	adl_key_right_shift = SDL_SCANCODE_RSHIFT,

	adl_key_left_alt = SDL_SCANCODE_LALT,
	adl_key_right_alt = SDL_SCANCODE_RALT,
};

#endif // sdl_definitions_h__