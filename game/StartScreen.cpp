#include "StartScreen.h"


StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();
	mGameConfig = GameConfig::Instance();

	// Background
	mBackground = new Texture("StartScreenBackground.png");
	mBackground->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.5f));

	// Logo
	mLogo = new Texture("Logo.png");
	mLogo->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.39f));

	// Play Button
	mPlayButton = new Texture("CentralLabel.png");
	mPlayButton->Position(Vector2(mGameConfig->winWidth * 0.51f, mGameConfig->winHeight * 0.81f));

	mPlayText = new Texture("\'Enter\' to play", "DSRoundup.ttf", 50, { COLOR_DARKRED });
	mPlayText->Position(Vector2(mGameConfig->winWidth * 0.51f, mGameConfig->winHeight * 0.807f));
}

StartScreen::~StartScreen()
{
	Timer::Release();
	mTimer = nullptr;

	InputManager::Release();
	mInputMgr = nullptr;

	GameConfig::Release();
	mGameConfig = nullptr;

	// Background
	delete mBackground;
	mBackground = nullptr;

	// Logo
	delete mLogo;
	mLogo = nullptr;

	// Play Button
	delete mPlayButton;
	mPlayButton = nullptr;
	delete mPlayText;
	mPlayText = nullptr;
}

void StartScreen::Update()
{
}

void StartScreen::Render()
{
	mBackground->Render();
	mLogo->Render();
	mPlayButton->Render();
	mPlayText->Render();
}
