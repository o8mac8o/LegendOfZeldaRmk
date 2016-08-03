#pragma once
#include "Sprite.h"
#include "Point.h"
#include "LoadMenu.h"

#define MENU_SRC_X 3
#define MENU_SRC_Y 4
#define MENU_SRC_X_JUMP 259
#define MENU_SRC_Y_JUMP 243
#define MENU_ANIM_FRAMES 6
#define MENU_ANIM_THIRD_FRAMES 2
#define MENU_ANIM_FIFTH_FRAMES 4

#define BLACK_SCREEN_SRC_X 0
#define BLACK_SCREEN_SRC_Y 758

#define WATERFALL_SRC_X 346
#define WATERFALL_SRC_Y 513
#define WATERFALL_WIDTH 32
#define WATERFALL_HEIGHT 58
#define WATERFALL_DST_X 315.69f
#define WATERFALL_DST_Y 662.76f

#define STORY_SRC_X 521
#define STORY_SRC_Y 14

class MainMenu :
	public Sprite
{
public:
	MainMenu();
	~MainMenu();

	void Update();

	void PlayMenuAnim();
	void ChangeImage();
	void SetMenuImage();
	bool isImageSrcYDown();

	void ShowStory();
	void MakeMainMenuDisapear();
	void ChangeImageColor();
	void ScrollScreen();
	void StoryScroll();
	void ItemScroll();
	bool isItemScrollReady();
	void EndScroll();

	void ReturnToMainMenu();
	void InitializeTimers();

	bool isPlayerPressedStart();
	void ShowLoadMenu();

private:
	Sprite* waterFallBackground;
	Sprite* waterFallSplash;
	Sprite* waterFallWave;
	Sprite* story;
	Sprite* menuHeart;

	LoadMenu* loadMenu;

	float animTimer = 0;
	float animDelay = 0.25f;
	int imageID = -1;
	Point<int> menuImageSrcs;
	float storyTimer = 0;
	int storyDelay = 10;

	float menuAndStoryMovement = 0;
	bool isShowingStory = false;
	float storyMovement = 0;
	float storyMovementRate = 3.3f;
	int storyMovementEnd = 589;
	float endMovement = 0;
	float menuAndStoryMovementSpeed = 200;

	float colorChangeTimer = 0;
	float colorChangeDelay = 1.5f;
	int colorChangeDoneDelay = 3;
	float red = 224;
	float green = 252;
	int blue = 210;
	float colorChangeRate = 0.10f;
};

