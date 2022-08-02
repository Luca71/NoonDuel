#include "WordsLabel.h"

WordsLabel::WordsLabel()
{
	mGameConfig = GameConfig::Instance();
	mTimer = Timer::Instance();

	mCanShoot = false;

	InitWords();

	mWordText = new Texture("Shoot", mGameConfig->secondFont, mGameConfig->ScoreFontSize, { COLOR_DARKRED });
	mWordText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));

	mWordLabel = new Texture("CentralLabel.png");
	mWordLabel->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));

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
}

void WordsLabel::Start()
{
	Active(true);
}

void WordsLabel::Update()
{
	if (Active())
	{
		mSwapTimer += mTimer->DeltaTime();

		if (mSwapTimer >= mSwapSpeed)
		{
			if (mCount > 0)
			{
				mCurrentWordIndex = rand() % mCountTexs.size();
				
				// Check if index has been yet extracted;
				if (mCurrentWordIndex == tempIndex)
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

}

bool WordsLabel::CanShoot()
{
	return mCanShoot;
}

void WordsLabel::CanShoot(bool canShoot)
{
	mCanShoot = canShoot;
}

void WordsLabel::Stop() // If 'shoot' not yet exit this set mTex to 'shoot' and stop swap
{
	mText = mCountTexs[0];
	mText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.9f));
	mCanShoot = true;
}

void WordsLabel::Reset()
{
	mCount = 2 + rand() % mGameConfig->ShootWordsMaxCount;
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
