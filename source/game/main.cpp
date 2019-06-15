#include "common.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	game.init_window("adl Game Engine", 1920, 1080);
	game.start();

	return 0;
}