#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "../framework/AnimatedTexture.h"
#include "../framework/InputManager.h"
#include "../framework/GameConfig.h"
#include "Countdown.h"
#include "Scoreboard.h"

using namespace EasySDL;

class PlayScreen
{
public:

	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();

private:

	Timer* mTimer;
	InputManager* mInputMgr;
	GameConfig* mGameConfig;

	// Background
	Texture* mBackground;

	// Top Bar Scores
	Texture* mP1TextScore;
	Texture* mP1Label;
	Scoreboard* mP1Score;

	Texture* mP2TextScore;
	Texture* mP2Label;
	Scoreboard* mP2Score;

	// Countdown
	Countdown* mCountdown;

	// Bottom Bar Word
	Texture* mWordText;
	Texture* mWordLabel;


	// Player 1
	AnimatedTexture* mPlayer1;

};

#endif // _PLAYSCREEN_H
