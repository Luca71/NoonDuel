#include "WordsLabel.h"

WordsLabel::WordsLabel()
{
	mGameConfig = GameConfig::Instance();
	mTimer = Timer::Instance();

	mCanShoot = false;
	mCanSwap = true;

	InitWords();

	mWordText = new Texture("Shoot", mGameConfig->secondFont, mGameConfig->ScoreFontSize, { COLOR_DARKRED });
	mWordText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));

	mWordLabel = new Texture("CentralLabel.png");
	mWordLabel->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));
	
	mEndTextFailed = new Texture("FAILED!", mGameConfig->secondFont, 70, { COLOR_DARKRED });
	mEndTextFailed->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.5f));

	mEndTextWin = new Texture("YOU WIN THIS MATCH!", mGameConfig->secondFont, 70, { COLOR_DARKRED });
	mEndTextWin->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.5f));

	mPlayerWinGame = new Texture("GAME OVER!", mGameConfig->secondFont, 70, { COLOR_DARKRED });
	mPlayerWinGame->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.5f));

	mEndTextRestart = new Texture("\'SPACE\' for next turn", mGameConfig->secondFont, 40, { COLOR_DARKRED });
	mEndTextRestart->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.6f));

	mWinTextRestart = new Texture("\'ESCAPE\' for new game", mGameConfig->secondFont, 40, { COLOR_DARKRED });
	mWinTextRestart->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.6f));

	mEndTextLoosePoint = new Texture("You loose 1 point", mGameConfig->secondFont, 30, { COLOR_DARKRED });
	mEndTextLoosePoint->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));

	mEndTextEarnPoint = new Texture("You earn 1 point", mGameConfig->secondFont, 30, { COLOR_DARKRED });
	mEndTextEarnPoint->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));

	mSwapSpeed = 1.0f + ((float)rand() / RAND_MAX) * 3.0f;
	mSwapTimer = mSwapSpeed;
	mCount = 2 + rand() % mGameConfig->ShootWordsMaxCount;

	Active(false);
}

WordsLabel::~WordsLabel()
{
	GameConfig::Release();
	mGameConfig = nullptr;

	ClearTexts();
	ClearWords();

	delete mWordText;
	mWordText = nullptr;
	delete mWordLabel;
	mWordLabel = nullptr;
	delete mEndTextFailed;
	mEndTextFailed = nullptr;
	delete mEndTextWin;
	mEndTextWin = nullptr;
	delete mPlayerWinGame;
	mPlayerWinGame = nullptr;
	delete mEndTextRestart;
	mEndTextRestart = nullptr;
	delete mWinTextRestart;
	mWinTextRestart = nullptr;
	delete mEndTextLoosePoint;
	mEndTextLoosePoint = nullptr;
	delete mEndTextEarnPoint;
	mEndTextEarnPoint = nullptr;
}

void WordsLabel::Start()
{
	Active(true);
}

void WordsLabel::Update()
{
	if (Active() && mCanSwap)
	{
		mSwapTimer += mTimer->DeltaTime();

		if (mSwapTimer >= mSwapSpeed)
		{
			if (mCount > 0)
			{
				mCurrentWordIndex = rand() % mCountTexs.size();

				while (mCurrentWordIndex == tempIndex)
				{
					mCurrentWordIndex = rand() % mCountTexs.size();
				}
				
				// Swap words if not equal to 'shoot'
				if(mCurrentWordIndex != 0)
				{
					tempIndex = mCurrentWordIndex;
					mText = mCountTexs[mCurrentWordIndex];
					mCount--;
					mSwapTimer = 0.0f;
					mText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));
				}
				else
				{
					Stop();
				}
			}
			else
			{
				Stop();
			}
		}
	}
}

void WordsLabel::Render()
{
	mWordLabel->Render();

	if (Active())
	{
		mText->Render();
	}

	if (mEndTurnState == loose)			// Is game ended with loose?
	{
		mEndTextFailed->Render();
		mEndTextRestart->Render();
	}
	else if (mEndTurnState == win)
	{
		mEndTextWin->Render();
		mEndTextRestart->Render();
	}
	else if (mEndTurnState == winGame)
	{
		mPlayerWinGame->Render();
		mWinTextRestart->Render();
	}
}

bool WordsLabel::CanShoot()
{
	return mCanShoot;
}

void WordsLabel::CanShoot(bool canShoot)
{
	mCanShoot = canShoot;
}

void WordsLabel::LooseTurn()
{
	Stop();
	mText = mEndTextLoosePoint;
}

void WordsLabel::WinTurn()
{
	Stop();
	mText = mEndTextEarnPoint;
}

void WordsLabel::WinGame()
{
	Stop();
	mText = mEndTextEarnPoint;
}

void WordsLabel::Stop() // If 'shoot' not yet exit this set mTex to 'shoot' and stop swap
{
	mCanSwap = false;
	mText = mCountTexs[0];
	mText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));
	mCanShoot = true;
}

void WordsLabel::SetEndTurnState(ENDTURN_STATE state)
{
	mEndTurnState = state;

	switch (mEndTurnState)
	{
	case win:
		WinTurn();
		break;

	case loose:
		LooseTurn();
		break;

	case winGame:
		WinGame();
		break;

	case none:
		break;
	}
}

void WordsLabel::Reset()
{
	mSwapSpeed = 1.0f + ((float)rand() / RAND_MAX) * 3.0f;
	mSwapTimer = mSwapSpeed;

	mCount = 2 + rand() % mGameConfig->ShootWordsMaxCount;

	mEndTurnState = none;

	mCanSwap = true;
	mCanShoot = false;

	Active(false);
}

void WordsLabel::ClearTexts()
{
	for (int i = 0; i < mCountTexs.size(); i++)
	{
		delete mCountTexs[i];
		mCountTexs[i] = nullptr;
	}
	mCountTexs.clear();
}

void WordsLabel::ClearWords()
{
	mWords.clear();
}

void WordsLabel::InitWords()
{
	mWords = { "Shoot", "School", "Scholar", "Shoulder", "Shoes", "Scheme", "Score"};

	for (int i = 0; i < mWords.size(); i++)
	{
		mCountTexs.push_back(new Texture(mWords[i], mGameConfig->mainFont, mGameConfig->WordsFontSize, { COLOR_DARKRED }));
	}
}
