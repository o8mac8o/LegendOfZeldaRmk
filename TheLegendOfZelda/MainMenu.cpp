#include "MainMenu.h"

MainMenu::MainMenu()
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
	loadMenu = new LoadMenu();
	loadMenu->SetIsActive(false);
	loadMenu->SetVisible(false);
	gTimer->Reset();
}

MainMenu::~MainMenu()
{
	delete waterFallBackground;
	delete story;
	delete loadMenu;
}

void MainMenu::Update()
{
	animTimer += gTimer->GetDeltaTime();
	if (storyTimer < storyDelay)
	{
		PlayMenuAnim();
		storyTimer += gTimer->GetDeltaTime();
	}
	if (storyTimer >= storyDelay)
		ShowStory();
	if (isPlayerPressedStart())
	{
		ShowLoadMenu();
		loadMenu->MakeHeartSelectorVisible();
	}
}

void MainMenu::PlayMenuAnim()
{		
	if (animTimer > animDelay)
		ChangeImage();
	SetMenuImage();
}

void MainMenu::ChangeImage()
{
	imageID++;
	if (imageID > MENU_ANIM_FRAMES)
		imageID = 1;
	animTimer = 0;
}

void MainMenu::SetMenuImage()
{
	menuImageSrcs.x = MENU_SRC_X + imageID % 2 * MENU_SRC_X_JUMP;
	menuImageSrcs.y = MENU_SRC_Y + isImageSrcYDown() * MENU_SRC_Y_JUMP;
	SetSrcRect(menuImageSrcs.x, menuImageSrcs.y, MENU_HEIGHT, MENU_WIDTH);
}

bool MainMenu::isImageSrcYDown()
{
	if (imageID < MENU_ANIM_THIRD_FRAMES || 
		imageID > MENU_ANIM_FIFTH_FRAMES)
		return false;
	return true;
}

void MainMenu::ShowStory()
{
	if (!isShowingStory)
		MakeMainMenuDisapear();
	else
		ScrollScreen();
}

void MainMenu::MakeMainMenuDisapear()
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

void MainMenu::ChangeImageColor()
{
	red -= colorChangeTimer * colorChangeRate;
	green -= colorChangeTimer * colorChangeRate;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
}

void MainMenu::ScrollScreen()
{
	menuAndStoryMovement += gTimer->GetDeltaTime() * menuAndStoryMovementSpeed;
	SetSrcPosition(BLACK_SCREEN_SRC_X, BLACK_SCREEN_SRC_Y);
	StoryScroll();
	if (isItemScrollReady())
		ItemScroll();
	else
		EndScroll();
}

void MainMenu::StoryScroll()
{
	if (SCREEN_RESOLUTION_Y - menuAndStoryMovement > 0)
	{
		SetDstRect(0, 0 - menuAndStoryMovement, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
		waterFallBackground->SetVisible(false);
		story->SetDstRect(0, SCREEN_RESOLUTION_Y - menuAndStoryMovement, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	}
}

void MainMenu::ItemScroll()
{
	storyMovement += gTimer->GetDeltaTime() * menuAndStoryMovementSpeed / storyMovementRate;
	story->SetSrcRect(STORY_SRC_X, STORY_SRC_Y + storyMovement, MENU_HEIGHT, MENU_WIDTH);
}

bool MainMenu::isItemScrollReady()
{
	if (storyMovement < storyMovementEnd && SCREEN_RESOLUTION_Y - menuAndStoryMovement <= 0)
		return true;
	return false;
}

void MainMenu::EndScroll()
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

void MainMenu::ReturnToMainMenu()
{
	SetDstRect(0, 0, MENU_HEIGHT, MENU_WIDTH, SCREEN_SCALING);
	waterFallBackground->SetVisible(true);
	InitializeTimers();
}

void MainMenu::InitializeTimers()
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

bool MainMenu::isPlayerPressedStart()
{
	if (gInput->IsControllerButtonPressed(gInput->controller1, SDL_CONTROLLER_BUTTON_START))
		return true;
	return false;
}

void MainMenu::ShowLoadMenu()
{
	SetIsActive(false);
	SetVisible(false);
	waterFallBackground->SetIsActive(false);
	waterFallBackground->SetVisible(false);
	story->SetIsActive(false);
	story->SetVisible(false);
	loadMenu->SetIsActive(true);
	loadMenu->SetVisible(true);
}
