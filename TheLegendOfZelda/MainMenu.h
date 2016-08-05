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

#define WATERFALL_SRC_X 346
#define WATERFALL_SRC_Y 513
#define WATERFALL_WIDTH 32
#define WATERFALL_HEIGHT 58
#define WATERFALL_DST_X 314
#define WATERFALL_DST_Y 722

#define WATERFALL_TOP_SRC_X 384
#define WATERFALL_TOP_SRC_Y 512
#define WATERFALL_TOP_WIDTH 32
#define WATERFALL_TOP_HEIGHT 7
#define WATERFALL_TOP_DST_X 314
#define WATERFALL_TOP_DST_Y 707

#define WATERFALL_SPLASH_SRC_X 423
#define WATERFALL_SPLASH_SRC_Y 539
#define WATERFALL_SPLASH_SRC_Y2 551
#define WATERFALL_SPLASH_DST_Y 690

#define STORY_SRC_X 521
#define STORY_SRC_Y 14

class MainMenu :
	public Sprite
{
public:
	MainMenu();
	~MainMenu();

	void Update();

	void AnimateWaterfallTop();
	void SpawnWave();
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
	Sprite* waterFallTop;
	Sprite* waterFallSplash;
	Sprite* waterFallWave1;
	Sprite* waterFallWave2;
	Sprite* waterFallWave3;
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

