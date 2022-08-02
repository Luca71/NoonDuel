#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();
	mGameConfig = GameConfig::Instance();

	// Background
	mBackground = new Texture("PlayScreenBackground.png");
	mBackground->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.5f));

	// Top Bar Scores
	mP1TextScore = new Texture("SCORE", mGameConfig->secondFont, mGameConfig->TextScoreFontSize, { COLOR_DARKBROWN });
	mP1TextScore->Position(Vector2(mGameConfig->winWidth * 0.162f, mGameConfig->winHeight * 0.1f));
	mP1Label = new Texture("ScoreLabel.png");
	mP1Label->Position(Vector2(Vector2(mGameConfig->winWidth * 0.16f, mGameConfig->winHeight * 0.14f)));
	mP1Score = new Scoreboard();
	mP1Score->Position(Vector2(Vector2(mGameConfig->winWidth * 0.178f, mGameConfig->winHeight * 0.17f)));

	mP2TextScore = new Texture("SCORE", mGameConfig->secondFont, mGameConfig->TextScoreFontSize, { COLOR_DARKBROWN });
	mP2TextScore->Position(Vector2(mGameConfig->winWidth * 0.843f, mGameConfig->winHeight * 0.1f));
	mP2Label = new Texture("ScoreLabel.png");
	mP2Label->Position(Vector2(Vector2(mGameConfig->winWidth * 0.838f, mGameConfig->winHeight * 0.14f)));
	mP2Score = new Scoreboard();
	mP2Score->Position(Vector2(Vector2(mGameConfig->winWidth * 0.86f, mGameConfig->winHeight * 0.17f)));

	// Countdown
	mCountdown = new Countdown();
	mCountdown->Start();

	// Bottom Bar Word
	mWordText = new Texture("Shoot", mGameConfig->secondFont, mGameConfig->ScoreFontSize, { COLOR_DARKRED });
	mWordText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));
	mWordLabel = new Texture("CentralLabel.png");
	mWordLabel->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));

	// Player 1
	mPlayer1 = new AnimatedTexture("Shoot_S1.png", 0, 0, 360, 360, 5, 0.5f, AnimatedTexture::horizontal);
	mPlayer1->Position(Vector2(mGameConfig->winWidth * 0.2f, mGameConfig->winHeight * 0.75f));
}

PlayScreen::~PlayScreen()
{
	// Background
	delete mBackground;
	mBackground = nullptr;
	
	// Top Bar Scores
	delete mP1TextScore;
	mP1TextScore = nullptr;
	delete mP1Label;
	mP1Label = nullptr;
	delete mP1Score;
	mP1Score = nullptr;

	delete mP2TextScore;
	mP2TextScore = nullptr;
	delete mP2Label;
	mP2Label = nullptr;
	delete mP2Score;
	mP2Score = nullptr;

	// Countdown
	delete mCountdown;
	mCountdown = nullptr;

	// Bottom Bar Word
	delete mWordText;
	mWordText = nullptr;
	delete mWordLabel;
	mWordLabel = nullptr;

	// Player 1
	delete mPlayer1;
	mPlayer1 = nullptr;
}

void PlayScreen::Update()
{
	mPlayer1->Update();
	
	if (mCountdown->Active()) { mCountdown->Update(); }
}

void PlayScreen::Render()
{
	// Background
	mBackground->Render();
	
	// Top Bar Scores
	mP1Label->Render();
	mP1TextScore->Render();
	mP1Score->Render();

	mP2Label->Render();
	mP2TextScore->Render();
	mP2Score->Render();

	// Countdown
	if (mCountdown->Active()) { mCountdown->Render();}

	// Bottom Bar Word
	mWordLabel->Render();
	mWordText->Render();

	// Player 1
	mPlayer1->Render();
}
