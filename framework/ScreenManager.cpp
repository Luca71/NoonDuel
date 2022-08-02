#include "ScreenManager.h"

namespace EasySDL
{
	ScreenManager* ScreenManager::sInstance = nullptr;

	ScreenManager* ScreenManager::Instance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new ScreenManager();
		}
		return sInstance;
	}

	void ScreenManager::Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	ScreenManager::ScreenManager()
	{
		mInputMgr = InputManager::Instance();

		// For this game only
		mStartScreen = new StartScreen();
		mPlayScreen = new PlayScreen();

		mCurrentScreen = play;
	}

	ScreenManager::~ScreenManager()
	{
		mInputMgr = nullptr;

		// For this game only
		delete mStartScreen;
		mStartScreen = nullptr;

		delete mPlayScreen;
		mPlayScreen = nullptr;

	}

	void ScreenManager::Update()
	{

		switch (mCurrentScreen)
		{
		case start:
			mStartScreen->Update();
			if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN))
			{
				mCurrentScreen = play;
			}
			break;

		case play:
			mPlayScreen->Update();
			if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
			{
				mCurrentScreen = start;
			}
			break;
		}
	}

	void ScreenManager::Render()
	{
		switch (mCurrentScreen)
		{
		case start:
			mStartScreen->Render();
			break;

		case play:
			mPlayScreen->Render();
			break;
		}
	}
}
