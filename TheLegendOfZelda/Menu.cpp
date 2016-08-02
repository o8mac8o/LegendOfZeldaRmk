#include "Menu.h"
#include "Menu.h"



Menu::Menu()
	:Sprite("Ressources/Sprites/Menus/Menu.png")
{
	menuImageSrcs.x = MENU_SRC_X;
	menuImageSrcs.y = MENU_SRC_Y;
	SetDstRect(0, 0, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	waterFallBackground = new Sprite("Ressources/Sprites/Menus/Menu.png");
	waterFallBackground->SetSrcRect(WATERFALL_SRC_X, WATERFALL_SRC_Y, WATERFALL_HEIGHT, WATERFALL_WIDTH);
	waterFallBackground->SetDstRect(WATERFALL_DST_X, WATERFALL_DST_Y, WATERFALL_HEIGHT,
		WATERFALL_WIDTH, SCREEN_SCALING);
	story = new Sprite("Ressources/Sprites/Menus/Menu.png");
	story->SetSrcRect(STORY_SRC_X, STORY_SRC_Y, MENU_HEIGHT, MENU_WIDTH);
	story->SetDstRect(0, SCREEN_RESOLUTION_Y, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
}

Menu::~Menu()
{
	delete waterFallBackground;
}

void Menu::Update()
{
	animTimer += gTimer->GetDeltaTime();
	if (storyTimer < 10)
	{
		PlayMenuAnim();
		storyTimer += gTimer->GetDeltaTime();
	}
	if (storyTimer > 10)
		ShowStory();
}

void Menu::PlayMenuAnim()
{		
	if (animTimer > animDelay)
		ChangeImage();
	SetMenuImage();
}

void Menu::ChangeImage()
{
	imageID++;
	if (imageID > MENU_ANIM_FRAMES)
		imageID = 1;
	animTimer = 0;
}

void Menu::SetMenuImage()
{
	menuImageSrcs.x = MENU_SRC_X + imageID % 2 * MENU_SRC_X_JUMP;
	menuImageSrcs.y = MENU_SRC_Y + isImageSrcYDown() * MENU_SRC_Y_JUMP;
	SetSrcRect(menuImageSrcs.x, menuImageSrcs.y, MENU_HEIGHT, MENU_WIDTH);
}

bool Menu::isImageSrcYDown()
{
	if (imageID < MENU_ANIM_THIRD_FRAMES || 
		imageID > MENU_ANIM_FIFTH_FRAMES)
		return false;
	return true;
}

void Menu::ShowStory()
{
	if (!isShowingStory)
		MakeMainMenuDisapear();
	else
		ScrollScreen();
}

void Menu::MakeMainMenuDisapear()
{
	colorChangeTimer += gTimer->GetDeltaTime();
	ChangeImageColor();
	SDL_SetTextureColorMod(image, red, green, blue);
	if (colorChangeTimer > colorChangeDoneDelay)
	{
		isShowingStory = true;
		SDL_SetTextureColorMod(image, 255, 255, 255);
	}
}

void Menu::ChangeImageColor()
{
	red -= colorChangeTimer * colorChangeRate;
	green -= colorChangeTimer * colorChangeRate;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
}

void Menu::ScrollScreen()
{
	menuAndStoryMovement += gTimer->GetDeltaTime() * menuAndStoryMovementSpeed;
	SetSrcPosition(BLACK_SCREEN_SRC_X, BLACK_SCREEN_SRC_Y);
	StoryScroll();
	if (isItemScrollReady())
		ItemScroll();
	else
		EndScroll();
}

void Menu::StoryScroll()
{
	if (SCREEN_RESOLUTION_Y - menuAndStoryMovement > 0)
	{
		SetDstRect(0, 0 - menuAndStoryMovement, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
		waterFallBackground->SetVisible(false);
		story->SetDstRect(0, SCREEN_RESOLUTION_Y - menuAndStoryMovement, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	}
}

void Menu::ItemScroll()
{
	storyMovement += gTimer->GetDeltaTime() * menuAndStoryMovementSpeed / storyMovementRate;
	story->SetSrcRect(STORY_SRC_X, STORY_SRC_Y + storyMovement, MENU_HEIGHT, MENU_WIDTH);
}

bool Menu::isItemScrollReady()
{
	if (storyMovement < storyMovementEnd && SCREEN_RESOLUTION_Y - menuAndStoryMovement <= 0)
		return true;
	return false;
}

void Menu::EndScroll()
{
	if (storyMovement >= storyMovementEnd)
	{
		endMovement += gTimer->GetDeltaTime() * menuAndStoryMovementSpeed;
		story->SetDstRect(0, GetX() - endMovement, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
		SetDstRect(0, SCREEN_RESOLUTION_Y - endMovement, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	}
	if (endMovement > storyMovementEnd + MENU_HEIGHT + 120)
		ReturnToMainMenu();
}

void Menu::ReturnToMainMenu()
{
	SetDstRect(0, 0, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	waterFallBackground->SetVisible(true);
	InitializeTimers();
}

void Menu::InitializeTimers()
{
	storyTimer = 0;
	menuAndStoryMovement = 0;
	storyMovement = 0;
	animTimer = 0;
	isShowingStory = false;
	endMovement = 0;
	colorChangeTimer = 0;
	story->SetSrcRect(STORY_SRC_X, STORY_SRC_Y, MENU_HEIGHT, MENU_WIDTH);
}
