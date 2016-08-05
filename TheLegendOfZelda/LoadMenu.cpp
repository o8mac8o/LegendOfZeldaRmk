#include "LoadMenu.h"



LoadMenu::LoadMenu()
	:Sprite("Ressources/Sprites/Menus/Menu.png")
{
	SetSrcRect(LOAD_MENU_SRC_X, LOAD_MENU_SRC_Y, MENU_HEIGHT, MENU_WIDTH);
	SetDstRect(0, 0, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	heartSelector = new Sprite("Ressources/Sprites/Menus/Menu.png");
	heartSelector->SetSrcRect(HEART_SRC_X, HEART_SRC_Y, HEART_HEIGHT, HEART_WIDTH);
	heartSelector->SetDstRect(HEART_DST_X, HEART_DST_Y, HEART_HEIGHT, HEART_WIDTH, SCREEN_SCALING);
	heartSelector->SetVisible(false);
	LoadGames();
	registerNameTop = new Sprite("Ressources/Sprites/Menus/Menu.png");
	registerNameTop->SetSrcRect(REGISTER_TOP_SRC_X, REGISTER_TOP_SRC_Y, REGISTER_TOP_HEIGHT, REGISTER_TOP_WIDTH);
	registerNameTop->SetDstRect(REGISTER_TOP_DST_X, REGISTER_TOP_DST_X, REGISTER_TOP_HEIGHT, REGISTER_TOP_WIDTH, SCREEN_SCALING);
	registerNameTop->SetVisible(false);
	registerNameMid = new Sprite("Ressources/Sprites/Menus/Menu.png");
	registerNameMid->SetSrcRect(REGISTER_MID_SRC_X, REGISTER_MID_SRC_Y, REGISTER_MID_HEIGHT, REGISTER_MID_WIDTH);
	registerNameMid->SetDstRect(REGISTER_MID_DST_X, REGISTER_MID_DST_Y, REGISTER_MID_HEIGHT, REGISTER_MID_WIDTH, SCREEN_SCALING);
	registerNameMid->SetVisible(false);
	registerNameBottom = new Sprite("Ressources/Sprites/Menus/Menu.png");
	registerNameBottom->SetSrcRect(REGISTER_BOT_SRC_X, REGISTER_BOT_SRC_Y, REGISTER_BOT_HEIGHT, REGISTER_BOT_WIDTH);
	registerNameBottom->SetDstRect(REGISTER_BOT_DST_X, REGISTER_BOT_DST_Y, REGISTER_BOT_HEIGHT, REGISTER_BOT_WIDTH, SCREEN_SCALING);
	registerNameBottom->SetVisible(false);
	registerNameSelector = new Sprite("Ressources/Sprites/Menus/Menu.png");
	registerNameSelector->SetSrcRect(REGISTER_SELECTOR_SRC_X, REGISTER_SELECTOR_SRC_Y, REGISTER_SELECTOR_SIZE, REGISTER_SELECTOR_SIZE);
	registerNameSelector->SetDstRect(REGISTER_SELECTOR_DST_X, REGISTER_SELECTOR_DST_Y, REGISTER_SELECTOR_SIZE, REGISTER_SELECTOR_SIZE, SCREEN_SCALING);
	registerNameSelector->SetVisible(false);
	CreateLetterArray();

	selectorMoveSound = Mix_LoadWAV("Ressources/Sounds/Effects/LOZ_Get_Rupee.wav");
}


LoadMenu::~LoadMenu()
{
	delete heartSelector;
	delete registerNameTop;
	delete registerNameMid;
	delete registerNameBottom;
	delete registerNameSelector;

	//Does not seems to be needed
	//for (int i = 0; i < REGISTER_ARRAY_X; i++)
	//{
	//	for (int j = 0; j < REGISTER_ARRAY_Y; j++)
	//	{
	//		delete registerArray[i][j];
	//	}
	//}
}

void LoadMenu::CreateLetterArray()
{
	std::ifstream ifs("Ressources/Sprites/Link/RegisterArray.json");
	minijson::istream_context ctx(ifs);

	int i = 0;
	int j = 0;
	minijson::parse_object(ctx, [&](const char* name, minijson::value value)
	{
		parse_array(ctx, [&](minijson::value v)
		{
			if (i < REGISTER_ARRAY_X)
			{
				registerArray[i][j] = new Text(REGISTER_ARRAY_DST_X + REGISTER_ARRAY_OFFSET * i,
					REGISTER_ARRAY_DST_Y + REGISTER_ARRAY_OFFSET * j, "emulogic.ttf", v.as_string(), FONT_SIZE);
			}
			else
			{
				i = 0;
				j++;
				registerArray[i][j] = new Text(REGISTER_ARRAY_DST_X + REGISTER_ARRAY_OFFSET * i,
					REGISTER_ARRAY_DST_Y + REGISTER_ARRAY_OFFSET * j, "emulogic.ttf", v.as_string(), FONT_SIZE);
			}
			registerArray[i][j]->SetVisible(false);
			i++;
		});
	});
}

void LoadMenu::Update()
{
	MoveHeartSelectorPosition();
	ShowHeartSelector();
	if (gInput->IsControllerButtonPressed(gInput->controller1, SDL_CONTROLLER_BUTTON_BACK))
		MakeChoice();
}

void LoadMenu::MakeChoice()
{
	if (isChoiceValid())
	{
		switch (heartPos)
		{
		case GAME1:
			//start game with game1
			break;
		case GAME2:
			//start game with game2
			break;
		case GAME3:
			//start game with game3
			break;
		case REGISTER:
			RegisterName();
			break;
		case ELIMINATE:
			break;
		default:
			break;
		}
	}
}

bool LoadMenu::isChoiceValid()
{
	switch (heartPos)
	{
	case GAME1:
		if (saves[GAME1].GetName().size() == 0)
			return false;
		break;
	case GAME2:
		if (saves[GAME2].GetName().size() == 0)
			return false;
		break;
	case GAME3:
		if (saves[GAME3].GetName().size() == 0)
			return false;
		break;
	case REGISTER:
		return true;
		break;
	case ELIMINATE:
		return true;
		break;
	default:
		return true;
		break;
	}
	return true;
}

void LoadMenu::RegisterName()
{
	SetSrcPosition(BLACK_SCREEN_SRC_X, BLACK_SCREEN_SRC_Y);
	registerNameTop->SetVisible(true);
	registerNameMid->SetVisible(true);
	registerNameBottom->SetVisible(true);
	registerNameSelector->SetVisible(true);
	registerNameSelector->StartFlashing(flashSpeed, flashSpeed);
	for (int i = 0; i < REGISTER_ARRAY_X; i++)
	{
		for (int j = 0; j < REGISTER_ARRAY_Y; j++)
		{
			registerArray[i][j]->SetVisible(true);
		}
	}
}

void LoadMenu::MoveHeartSelectorPosition()
{
	if ((gInput->IsControllerButtonPressed(gInput->controller1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		gInput->IsKeyHeld(SDL_SCANCODE_DOWN)) && heartPos < ELIMINATE)
	{
		Mix_PlayChannel(-1, selectorMoveSound, 0);
		heartPos++;
	}
	if ((gInput->IsControllerButtonPressed(gInput->controller1, SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		gInput->IsKeyHeld(SDL_SCANCODE_UP)) && heartPos > GAME1)
	{
		Mix_PlayChannel(-1, selectorMoveSound, 0);
		heartPos--;
	}
}

void LoadMenu::ShowHeartSelector()
{
	if(heartPos < REGISTER)
		heartSelector->SetPosition(HEART_DST_X, HEART_DST_Y + heartPos * HEART_DISPLACEMENT);
	else
		heartSelector->SetPosition(HEART_DST_X, HEART_DST2_Y + (heartPos - GAME3) * HEART_DISPLACEMENT2);
}

void LoadMenu::LoadGames()
{
	std::ifstream ifs("Ressources/Sprites/Link/SaveGame.json");
	minijson::istream_context ctx(ifs);
	int gameNumber = 0;

	minijson::parse_object(ctx, [&](const char* name, minijson::value value)
	{
		parse_array(ctx, [&](minijson::value v)
		{
			parse_object(ctx, [&](const char* k, minijson::value value)
			{
				parse_object(ctx, [&](const char* r, minijson::value value)
				{
					minijson::dispatch(r)
					<< "name" >> [&] { saves[gameNumber].SetName(value.as_string()); }
					<< "numberofhearts" >> [&] { saves[gameNumber].SetNumberOfHearts(value.as_double()); }
					<< "numberofRupees" >> [&] { saves[gameNumber].SetNumberOfRupees(value.as_double()); }
					<< "numberofkeys" >> [&] { saves[gameNumber].SetNumberOfKeys(value.as_double()); }
					<< "numberofbombs" >> [&] { saves[gameNumber].SetNumberOfBombs(value.as_double()); }
					<< "swordlevel" >> [&] { saves[gameNumber].SetSwordlevel(value.as_double()); gameNumber++; }					

					<< "name" >> [&] { saves[gameNumber].SetName(value.as_string()); }
					<< "numberofhearts" >> [&] { saves[gameNumber].SetNumberOfHearts(value.as_double()); }
					<< "numberofRupees" >> [&] { saves[gameNumber].SetNumberOfRupees(value.as_double()); }
					<< "numberofkeys" >> [&] { saves[gameNumber].SetNumberOfKeys(value.as_double()); }
					<< "numberofbombs" >> [&] { saves[gameNumber].SetNumberOfBombs(value.as_double()); }
					<< "swordlevel" >> [&] { saves[gameNumber].SetSwordlevel(value.as_double()); gameNumber++; }

					<< "name" >> [&] { saves[gameNumber].SetName(value.as_string()); }
					<< "numberofhearts" >> [&] { saves[gameNumber].SetNumberOfHearts(value.as_double()); }
					<< "numberofRupees" >> [&] { saves[gameNumber].SetNumberOfRupees(value.as_double()); }
					<< "numberofkeys" >> [&] { saves[gameNumber].SetNumberOfKeys(value.as_double()); }
					<< "numberofbombs" >> [&] { saves[gameNumber].SetNumberOfBombs(value.as_double()); }
					<< "swordlevel" >> [&] { saves[gameNumber].SetSwordlevel(value.as_double()); std::cout << gameNumber; }

					<< minijson::any >> [&] { ignore(ctx); };
				});
			});
		});
	});
}
