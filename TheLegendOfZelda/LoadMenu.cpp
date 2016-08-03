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
}


LoadMenu::~LoadMenu()
{
	delete heartSelector;
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
		LoadGames();
	}
}

bool LoadMenu::isChoiceValid()
{
	return true;
}

void LoadMenu::MoveHeartSelectorPosition()
{
	if ((gInput->IsControllerButtonPressed(gInput->controller1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		gInput->IsKeyHeld(SDL_SCANCODE_DOWN)) && heartPos < ELIMINATE)
	{
		heartPos++;
	}
	if ((gInput->IsControllerButtonPressed(gInput->controller1, SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		gInput->IsKeyHeld(SDL_SCANCODE_UP)) && heartPos > GAME1)
	{
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

	minijson::parse_object(ctx, [&](const char* name, minijson::value value)
	{
		parse_array(ctx, [&](minijson::value v)
		{
			parse_object(ctx, [&](const char* k, minijson::value value)
			{
				parse_object(ctx, [&](const char* r, minijson::value value)
				{
					minijson::dispatch(r)
					<< "name" >> [&] { name1 = value.as_string(); }
					<< "numberofhearts" >> [&] { game1numberOfHearts = value.as_double(); }
					<< "numberofRupees" >> [&] { game1numberofRupees = value.as_double(); }
					<< "numberofkeys" >> [&] { game1numberofkeys = value.as_double(); }
					<< "numberofbombs" >> [&] { game1numberofbombs = value.as_double(); }
					<< "swordlevel" >> [&] { game1swordlevel = value.as_double(); }	
					<< "name" >> [&] { name2 = value.as_string(); }
					<< "numberofhearts" >> [&] { game2numberOfHearts = value.as_double(); }
					<< "numberofRupees" >> [&] { game2numberofRupees = value.as_double(); }
					<< "numberofkeys" >> [&] { game2numberofkeys = value.as_double(); }
					<< "numberofbombs" >> [&] { game2numberofbombs = value.as_double(); }
					<< "swordlevel" >> [&] { game2swordlevel = value.as_double(); }
					<< "name" >> [&] { name3 = value.as_string(); }
					<< "numberofhearts" >> [&] { game3numberOfHearts = value.as_double(); }
					<< "numberofRupees" >> [&] { game3numberofRupees = value.as_double(); }
					<< "numberofkeys" >> [&] { game3numberofkeys = value.as_double(); }
					<< "numberofbombs" >> [&] { game3numberofbombs = value.as_double(); }
					<< "swordlevel" >> [&] { game3swordlevel = value.as_double(); }
					<< minijson::any >> [&] { ignore(ctx); };
				});
			});
		});
	});
}
