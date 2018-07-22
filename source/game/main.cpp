#include "common.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	game.create_window("Default Window", 800, 600);
	game.start();

	return 0;
}