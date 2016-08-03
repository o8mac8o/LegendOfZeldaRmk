#pragma once
#include "Sprite.h"
#include "minijson_reader.hpp"

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

class LoadMenu :
	public Sprite
{
public:
	LoadMenu();
	~LoadMenu();

	void LoadGame();

private:
	char buffer[5270447];
};

