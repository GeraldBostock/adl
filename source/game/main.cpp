#include "common.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	game.init_window("Default Window", 1280, 720);
	game.start();

	return 0;
}