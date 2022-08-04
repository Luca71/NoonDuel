#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();
	mGameConfig = GameConfig::Instance();

	mCanShoot = false;
	mCurrentTurnState = start;

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
	mPlayer1 = new Player("Idle_S1.png", "Shoot_S1.png", "Dead_S1.png", Vector2(mGameConfig->winWidth * 0.2f, mGameConfig->winHeight * 0.74f));

	// Player 2
	mPlayer2 = new Player("Idle_S2.png", "Shoot_S2.png", "Dead_S2.png", Vector2(mGameConfig->winWidth * 0.8f, mGameConfig->winHeight * 0.74f), true);

	// Player 1 fails
	Texture* temp = new Texture("Fail.png");
	temp->Position(Vector2(mGameConfig->winWidth * 0.26f, mGameConfig->winHeight * 0.17f));
	temp->Active(false);
	mP1Fails.push_back(temp);

	temp = new Texture("Fail.png");
	temp->Position(Vector2(mGameConfig->winWidth * 0.23f, mGameConfig->winHeight * 0.17f));
	temp->Active(false);
	mP1Fails.push_back(temp);

	// Player 2 fails
	temp = new Texture("Fail.png");
	temp->Position(Vector2(mGameConfig->winWidth * 0.74f, mGameConfig->winHeight * 0.17f));
	temp->Active(false);
	mP2Fails.push_back(temp);

	temp = new Texture("Fail.png");
	temp->Position(Vector2(mGameConfig->winWidth * 0.77f, mGameConfig->winHeight * 0.17f));
	temp->Active(false);
	mP2Fails.push_back(temp);
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

	// Player 1 fails
	mP1Fails.clear();

	// Player 2 fails
	mP2Fails.clear();
}

void PlayScreen::StartTurn()
{
	mCurrentTurnState = running;
	mCountdown->Start(); // Start countdown
	mWordsLabel->Reset();
}

void PlayScreen::EndTurn()
{
	// TODO
	mCurrentTurnState = end;
	mWordsLabel->EndTurn();
	mWordsLabel->CanShoot(false);
	mPlayer1->CanShoot(false);
	mPlayer2->CanShoot(false);
}

void PlayScreen::Update()
{
	// If 'shoot' is in the label
	if (mWordsLabel->CanShoot())					
	{
		if (mInputMgr->KeyPressed(SDL_SCANCODE_A) && mCurrentTurnState == running)
		{
			mWordsLabel->CanShoot(false);
			if (mPlayer1->CanShoot())
			{
				mCurrentTurnState = end;

				mP1Score->IncrementScore();
				
				mPlayer1->SetState(Player::Shoot);
				mPlayer2->CanShoot(false);
				mPlayer2->SetState(Player::Dead);
			}
		}
		else if (mInputMgr->KeyPressed(SDL_SCANCODE_L) && mCurrentTurnState == running)
		{
			mWordsLabel->CanShoot(false);
			if (mPlayer2->CanShoot())
			{
				mCurrentTurnState = end;

				mP2Score->IncrementScore();

				mPlayer2->SetState(Player::Shoot);
				mPlayer1->CanShoot(false);
				mPlayer1->SetState(Player::Dead);
			}
		}

		if (mInputMgr->KeyPressed(SDL_SCANCODE_A) && mCurrentTurnState == end)
		{

		}
	}
	else
	{
		if (mInputMgr->KeyPressed(SDL_SCANCODE_A) && mCurrentTurnState == running)
		{
			if (mPlayer1->GetFails() < mP1Fails.size())
			{
				mP1Fails[mPlayer1->GetFails()]->Active(true);
				mPlayer1->IncrementFails();
			}
			else
			{
				// TODO end turn
				EndTurn();
				mP2Score->IncrementScore();
			}
		}
		else if (mInputMgr->KeyPressed(SDL_SCANCODE_L) && mCurrentTurnState == running)
		{
			if (mPlayer2->GetFails() < mP2Fails.size())
			{
				mP2Fails[mPlayer2->GetFails()]->Active(true);
				mPlayer2->IncrementFails();
			}
			else
			{
				// TODO end turn
				EndTurn();
				mP1Score->IncrementScore();
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

	// Player 1 fails
	for (int i = 0; i < mP1Fails.size(); i++)
	{
		if (mP1Fails[i]->Active())
		{
			mP1Fails[i]->Render();
		}
	}

	// Player 2 fails
	for (int i = 0; i < mP2Fails.size(); i++)
	{
		if (mP2Fails[i]->Active())
		{
			mP2Fails[i]->Render();
		}
	}
}
