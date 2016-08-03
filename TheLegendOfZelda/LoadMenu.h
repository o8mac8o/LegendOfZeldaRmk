#pragma once
#include "Sprite.h"

#include "minijson_reader.hpp"
#include "minijson_writer.hpp"

#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <stdio.h>

#define LOAD_MENU_SRC_X 3
#define LOAD_MENU_SRC_Y 504

#define MENU_WIDTH 255.0f
#define MENU_HEIGHT 239.0f

#define SCREEN_RESOLUTION_X 1000
#define SCREEN_RESOLUTION_Y 880
#define SCREEN_SCALING SCREEN_RESOLUTION_X / (float)MENU_WIDTH

#define HEART_SRC_X 594
#define HEART_SRC_Y 256
#define HEART_WIDTH 7
#define HEART_HEIGHT 8
#define HEART_DST_X 156.862f
#define HEART_DST_Y 360.784f
#define HEART_DST2_Y 600
#define HEART_DISPLACEMENT 94.118f
#define HEART_DISPLACEMENT2 60
#define HEART_REG 77
#define HEART_ELI 93
#define HEART_POS_SIZE 5

enum HEART_POSITION
{
	GAME1,
	GAME2,
	GAME3,
	REGISTER,
	ELIMINATE
};

class LoadMenu :
	public Sprite
{
public:
	LoadMenu();
	~LoadMenu();

	void Update();

	void MakeHeartSelectorVisible() { heartSelector->SetVisible(true); }
	void MoveHeartSelectorPosition();
	void ShowHeartSelector();

	void MakeChoice();
	bool isChoiceValid();

	void LoadGames();

private:
	Sprite* heartSelector;

	std::vector<int> gamesInfos;

	std::string name1;
	int game1numberOfHearts = 0;
	int game1numberofRupees = 0;
	int game1numberofkeys = 0;
	int game1numberofbombs = 0;
	int game1swordlevel = 0;

	std::string name2;
	int game2numberOfHearts = 0;
	int game2numberofRupees = 0;
	int game2numberofkeys = 0;
	int game2numberofbombs = 0;
	int game2swordlevel = 0;

	std::string name3;
	int game3numberOfHearts = 0;
	int game3numberofRupees = 0;
	int game3numberofkeys = 0;
	int game3numberofbombs = 0;
	int game3swordlevel = 0;

	int heartPos = 0;
};

