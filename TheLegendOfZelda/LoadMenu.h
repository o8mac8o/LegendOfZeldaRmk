#pragma once
#include "Sprite.h"
#include "SaveGame.h"
#include "Music.h"

#include "minijson_reader.hpp"
#include "minijson_writer.hpp"
#include "Text.h"

#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

#define LOAD_MENU_SRC_X 3
#define LOAD_MENU_SRC_Y 504

#define REGISTER_TOP_SRC_X 262
#define REGISTER_TOP_SRC_Y 617
#define REGISTER_TOP_DST_X 55 
#define REGISTER_TOP_DST_Y -2
#define REGISTER_TOP_HEIGHT 15
#define REGISTER_TOP_WIDTH  215

#define REGISTER_MID_SRC_X 53
#define REGISTER_MID_SRC_Y 593
#define REGISTER_MID_DST_X 290
#define REGISTER_MID_DST_Y 180
#define REGISTER_MID_HEIGHT 63
#define REGISTER_MID_WIDTH  32

#define REGISTER_BOT_SRC_X 262
#define REGISTER_BOT_SRC_Y 635
#define REGISTER_BOT_DST_X 80
#define REGISTER_BOT_DST_Y 485
#define REGISTER_BOT_HEIGHT 87
#define REGISTER_BOT_WIDTH  215

#define REGISTER_SELECTOR_SRC_X 262
#define REGISTER_SELECTOR_SRC_Y 734      
#define REGISTER_SELECTOR_DST_X 166
#define REGISTER_SELECTOR_DST_Y 563
#define REGISTER_SELECTOR_SIZE 8

#define MENU_WIDTH 255.0f
#define MENU_HEIGHT 239.0f

#define BLACK_SCREEN_SRC_X 0
#define BLACK_SCREEN_SRC_Y 758

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

#define REGISTER_ARRAY_X 11
#define REGISTER_ARRAY_Y 4
#define REGISTER_ARRAY_DST_X 162
#define REGISTER_ARRAY_DST_Y 555
#define REGISTER_ARRAY_OFFSET 16 * SCREEN_SCALING
#define FONT_SIZE 31


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

	void CreateLetterArray();

	void Update();

	void MakeHeartSelectorVisible() { heartSelector->SetVisible(true); }
	void MoveHeartSelectorPosition();

	void ShowHeartSelector();

	void MakeChoice();
	bool isChoiceValid();
	void RegisterName();

	void LoadGames();

private:
	Sprite* heartSelector;

	Sprite* registerNameTop;
	Sprite* registerNameMid;
	Sprite* registerNameBottom;
	Sprite* registerNameSelector;
	float flashSpeed = 0.15f;

	Text* registerArray[REGISTER_ARRAY_X][REGISTER_ARRAY_Y];

	SaveGame saves[3];

	Mix_Chunk* selectorMoveSound = NULL;

	int heartPos = 0;
};

