#include "LoadMenu.h"



LoadMenu::LoadMenu()
	:Sprite("Ressources/Sprites/Menus/Menu.png")
{
	SetSrcRect(LOAD_MENU_SRC_X, LOAD_MENU_SRC_Y, MENU_HEIGHT, MENU_WIDTH);
	SetDstRect(0, 0, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
}


LoadMenu::~LoadMenu()
{
}

void LoadMenu::LoadGame()
{
	std::ostringstream sstream;
	std::ifstream ifs("Ressources/Sprites/Link/SaveGame.json");
	sstream << ifs.rdbuf();
	const std::string str(sstream.str());
	const char* buffer1 = str.c_str();
	const size_t size = strlen(buffer1);
	sprintf_s(buffer, buffer1, sizeof(buffer));
	minijson::buffer_context ctx(buffer, sizeof(buffer) - 1);
}
