#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();
	mGameConfig = GameConfig::Instance();

	mCanShoot = false;

	// Background
	mBackground = new Texture("PlayScreenBackground.png");
	mBackground->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.5f));

	// Top Bar Scores
	mP1TextScore = new Texture("SCORE", mGameConfig->secondFont, mGameConfig->TextScoreFontSize, { COLOR_DARKBROWN });
	mP1TextScore->Position(Vector2(mGameConfig->winWidth * 0.162f, mGameConfig->winHeight * 0.1f));
	mP1Label = new Texture("ScoreLabel.png");
	mP1Label->Position(Vector2(mGameConfig->winWidth * 0.16f, mGameConfig->winHeight * 0.14f));
	mP1Score = new Scoreboard();
	mP1Score->Position(Vector2(mGameConfig->winWidth * 0.178f, mGameConfig->winHeight * 0.17f));
	mP1Key = new Texture("\'A\' to shoot", mGameConfig->secondFont, 30, { COLOR_DARKRED });
	mP1Key->Position(Vector2(mGameConfig->winWidth * 0.083f, mGameConfig->winHeight * 0.28f));

	mP2TextScore = new Texture("SCORE", mGameConfig->secondFont, mGameConfig->TextScoreFontSize, { COLOR_DARKBROWN });
	mP2TextScore->Position(Vector2(mGameConfig->winWidth * 0.843f, mGameConfig->winHeight * 0.1f));
	mP2Label = new Texture("ScoreLabel.png");
	mP2Label->Position(Vector2(mGameConfig->winWidth * 0.838f, mGameConfig->winHeight * 0.14f));
	mP2Score = new Scoreboard();
	mP2Score->Position(Vector2(mGameConfig->winWidth * 0.86f, mGameConfig->winHeight * 0.17f));
	mP2Key = new Texture("\'L\' to shoot", mGameConfig->secondFont, 30, { COLOR_DARKRED });
	mP2Key->Position(Vector2(mGameConfig->winWidth * 0.91f, mGameConfig->winHeight * 0.28f));

	// Countdown
	mCountdown = new Countdown();

	// Bottom Bar Word
	mWordsLabel = new WordsLabel();

	// Player 1
	mPlayer1 = new Player("Idle_S1.png", "Shoot_S1.png", "Dead_S1.png", Vector2(mGameConfig->winWidth * 0.2f, mGameConfig->winHeight * 0.75f));

	// Player 2
	mPlayer2 = new Player("Idle_S2.png", "Shoot_S2.png", "Dead_S2.png", Vector2(mGameConfig->winWidth * 0.8f, mGameConfig->winHeight * 0.75f), true);
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
	delete mP1Key;
	mP1Key = nullptr;

	delete mP2TextScore;
	mP2TextScore = nullptr;
	delete mP2Label;
	mP2Label = nullptr;
	delete mP2Score;
	mP2Score = nullptr;
	delete mP2Key;
	mP2Key = nullptr;

	// Countdown
	delete mCountdown;
	mCountdown = nullptr;

	// Bottom Bar Word
	delete mWordsLabel;
	mWordsLabel = nullptr;

	// Player 1
	delete mPlayer1;
	mPlayer1 = nullptr;

	// Player 2
	delete mPlayer2;
	mPlayer2 = nullptr;
}

void PlayScreen::StartTurn()
{
	mCountdown->Start(); // Start countdown
}

void PlayScreen::Update()
{
	// If 'shoot' is in the label
	if (mWordsLabel->CanShoot())					
	{
		if (mInputMgr->KeyPressed(SDL_SCANCODE_A))
		{
			mWordsLabel->CanShoot(false);
			if (mPlayer1->CanShoot())
			{
				mPlayer1->SetState(Player::Shoot);
				mPlayer2->CanShoot(false);
			}
		}
		else if (mInputMgr->KeyPressed(SDL_SCANCODE_L))
		{
			mWordsLabel->CanShoot(false);
			if (mPlayer2->CanShoot())
			{
				mPlayer2->SetState(Player::Shoot);
				mPlayer1->CanShoot(false);
			}
		}
	}
	
	mPlayer1->Update();
	mPlayer2->Update();
	
	if (mCountdown->Active())	// If countdown is running
	{
		mCountdown->Update();
	}
	else						// if not -> Update WordsLabel
	{
		mWordsLabel->Start();
	}

	if (mWordsLabel->Active())
	{
		mWordsLabel->Update();
	}
}

void PlayScreen::Render()
{
	// Background
	mBackground->Render();
	
	// Top Bar Scores
	mP1Label->Render();
	mP1TextScore->Render();
	mP1Score->Render();
	mP1Key->Render();

	mP2Label->Render();
	mP2TextScore->Render();
	mP2Score->Render();
	mP2Key->Render();

	// Countdown
	if (mCountdown->Active()) { mCountdown->Render();}

	// Bottom Bar Word
	mWordsLabel->Render();

	// Player 1
	mPlayer1->Render();

	// Player 2
	mPlayer2->Render();
}
