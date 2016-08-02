#include "Game.h"

Game::Game()
{
	gEngine->SetScreenRes(1000, 880, 0);
	gameMenu = new Menu();
}


Game::~Game()
{
	delete gameMenu;
}
