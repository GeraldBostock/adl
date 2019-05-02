#include "common.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	game.init_window("adl Game Engine", 1366, 768);
	game.start();

	return 0;
}