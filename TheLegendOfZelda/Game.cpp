#include "Game.h"

Game::Game()
{
	gEngine->SetScreenRes(1000, 880, 0);
	gameMenu = new MainMenu();
}


Game::~Game()
{
	delete gameMenu;
}
