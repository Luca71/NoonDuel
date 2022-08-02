#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "../framework/AnimatedTexture.h"
#include "../framework/InputManager.h"
#include "../framework/GameConfig.h"

using namespace EasySDL;

class StartScreen : GameEntity
{
public:

	StartScreen();
	~StartScreen();

	void Update();
	void Render();


private:

	Timer* mTimer;
	InputManager* mInputMgr;
	GameConfig* mGameConfig;

	// Background
	Texture* mBackground;

	//Logo
	Texture* mLogo;

	// Play Button
	Texture* mPlayButton;
	Texture* mPlayText;

	// sound
};



#endif // _STARTSCREEN_H
