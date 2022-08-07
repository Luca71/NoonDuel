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
		mAudioMgr = AudioManager::Instance();

		// For this game only
		mStartScreen = new StartScreen();
		mPlayScreen = new PlayScreen();

		mCurrentScreen = start;
	}

	ScreenManager::~ScreenManager()
	{
		InputManager::Release();
		mInputMgr = nullptr;

		AudioManager::Release();
		mAudioMgr = nullptr;

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

			if (mAudioMgr->IsMusicPaused()) { mStartScreen->PlayMusic(); }

			if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN))
			{
				mCurrentScreen = play;
				mPlayScreen->StartTurn();
				mAudioMgr->PauseMusic();
				mAudioMgr->PlaySFX("click.wav");
			}
			break;

		case play:
			mPlayScreen->Update();

			if (mAudioMgr->IsMusicPaused()) { mPlayScreen->PlayMusic(); }

			if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
			{
				mPlayScreen->NewGame();
				mCurrentScreen = start;
				mAudioMgr->PauseMusic();
				mAudioMgr->PlaySFX("click.wav");
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
