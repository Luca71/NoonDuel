#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "InputManager.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "ScreenManager.h"

namespace EasySDL
{
	class GameManager
	{
	public:
	
		static  GameManager* Instance();
		static void Release();
	
		void Run();
	
	private:
	
		GameManager();
		~GameManager();
	
		static GameManager* sInstance;
	
		Timer* mTimer;
		const int FRAME_RATE = 60;

		void EarlyUpdate();
		void Update();
		void LateUpdate();
	
		void Render();
	
		bool mQuit;
		Graphics* mGraphics;
		AssetManager* mAssetMgr;
		InputManager* mInputMgr;
		AudioManager* mAudioMgr;
		ScreenManager* mScreenMgr;

		SDL_Event mEvents;
	
		// For this game only
	
	
	};
}

#endif // _GAMEMANAGER_H
