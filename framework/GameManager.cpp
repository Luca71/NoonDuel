#include "GameConfig.h"
#include "GameManager.h"
#include <time.h>


namespace EasySDL
{
	GameManager* GameManager::sInstance = nullptr;
	
	GameManager* GameManager::Instance()
	{
		if (sInstance == NULL)
		{
			sInstance = new GameManager();
		}
		return sInstance;
	}
	
	void GameManager::Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}
	
	GameManager::GameManager()
	{
		srand(time(0));

		mQuit = false;
		mGraphics = Graphics::Instance();
		if (!Graphics::Initialized())
		{
			mQuit = true;
		}
	
		mAssetMgr = AssetManager::Instance();
		mInputMgr = InputManager::Instance();
		mAudioMgr = AudioManager::Instance();
		mScreenMgr = ScreenManager::Instance();
	
		mTimer = Timer::Instance();
	}
	
	GameManager::~GameManager()
	{
		ScreenManager::Release();
		mScreenMgr = nullptr;
		
		AudioManager::Release();
		mAudioMgr = nullptr;
		
		AssetManager::Release();
		mAssetMgr = nullptr;
	
		Graphics::Release();
		mGraphics = nullptr;
	
		InputManager::Release();
		mInputMgr = nullptr;
	
		Timer::Release();
		mTimer = nullptr;
	}
	
	/**
	 * Update the input here
	 */
	void GameManager::EarlyUpdate()
	{
		mTimer->Reset();
		mInputMgr->Update();
	}
	
	/**
	 * GameEntity updates should happen here
	 */
	void GameManager::Update()
	{
		mScreenMgr->Update();
	}
	
	/**
	 * Any collision detection should happen here
	 */
	void GameManager::LateUpdate()
	{
		mInputMgr->UpdatePrevInput();
	}
	
	void GameManager::Render()
	{
		// Start of render
		mGraphics->ClearBackBuffer();

		// For this game only
		mScreenMgr->Render();
	
		// End of render
		mGraphics->Render();
	}
	
	void GameManager::Run()
	{
		while (!mQuit)
		{
	
			mTimer->Update();
	
			while (SDL_PollEvent(&mEvents) != 0)
			{
				if (mEvents.type == SDL_QUIT)
				{
					mQuit = true;
				}
			}
			
			if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
			{
				EarlyUpdate();
				Update();
				LateUpdate();
				Render();
			}
		}
	}
}
