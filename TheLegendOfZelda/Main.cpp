#include "Engine.h"

#include "Game.h"

int main(int argc, char* args[])
{
	gEngine->Init();

	Game game;// = new Game();

	int assert = gEngine->Run();

	//delete game;


	return assert;
}