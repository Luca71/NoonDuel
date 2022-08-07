#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "InputManager.h"
#include "AudioManager.h"
#include "../game/StartScreen.h"
#include "../game/PlayScreen.h"

namespace EasySDL
{
	class ScreenManager
	{
	public:
	
		static ScreenManager* Instance();
		static void Release();
	
		void Update();
		void Render();
	
	private:
	
		ScreenManager();
		~ScreenManager();

		static ScreenManager* sInstance;

		enum SCREENS { start, play };

		InputManager* mInputMgr;
		AudioManager* mAudioMgr;

		SCREENS mCurrentScreen;

		// for this game
		StartScreen* mStartScreen;
		PlayScreen* mPlayScreen;
	};
}


#endif // _SCREENMANAGER_H
