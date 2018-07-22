#include "Game.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlInput.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	return true;
}

bool Game::update(double dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}
	return true;
}