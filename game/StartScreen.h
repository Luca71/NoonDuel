#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "../framework/AnimatedTexture.h"
#include "../framework/InputManager.h"
#include "../framework/GameConfig.h"
#include "../framework/AudioManager.h"

using namespace EasySDL;

class StartScreen : GameEntity
{
public:

	StartScreen();
	~StartScreen();

	void Update();
	void Render();

	void PlayMusic();

private:

	Timer* mTimer;
	InputManager* mInputMgr;
	GameConfig* mGameConfig;
	AudioManager* mAudioMgr;

	// Background
	Texture* mBackground;

	//Logo
	Texture* mLogo;

	// Play Button
	Texture* mPlayButton;
	Texture* mPlayText;

};



#endif // _STARTSCREEN_H
