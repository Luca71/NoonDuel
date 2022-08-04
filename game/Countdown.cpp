#include "Countdown.h"

Countdown::Countdown()
{
	mGameConfig = GameConfig::Instance();
	mTimer = Timer::Instance();

	for (int i = 0; i < 3; i++)
	{
		mCountTexs.push_back(new Texture(std::to_string(i+1), mGameConfig->mainFont, mGameConfig->CounterFontSize, { COLOR_GRAY }));
	}

	mText = mCountTexs[0];

	mSwapSpeed = 1.0f;
	mSwapTimer = mSwapSpeed;
	mCount = 3;

	Active(false);
}

Countdown::~Countdown()
{
	GameConfig::Release();
	mGameConfig = nullptr;

	ClearTexts();
}

void Countdown::Start()
{
	Active(true);
	Reset();
}

void Countdown::Update()
{
	if (Active())
	{
		mSwapTimer += mTimer->DeltaTime();
	
		if (mSwapTimer >= mSwapSpeed)
		{
			if (mCount > 0)
			{
				mText = mCountTexs[mCount - 1];
				mCount--;
				mSwapTimer = 0.0f;

				mText->Position(Vector2(mGameConfig->winWidth * 0.5f, mGameConfig->winHeight * 0.15f));
			}
			else
			{
				Active(false);
			}
		}
	}
}

void Countdown::Render()
{
	if (Active()) { mText->Render(); }
}

void Countdown::Reset()
{
	mCount = 3;
}

void Countdown::ClearTexts()
{
	for (int i = 0; i < mCountTexs.size(); i++)
	{
		delete mCountTexs[i];
		mCountTexs[i] = nullptr;
	}
	mCountTexs.clear();
}
