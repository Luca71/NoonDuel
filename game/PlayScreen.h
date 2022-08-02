#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "../framework/AnimatedTexture.h"
#include "../framework/InputManager.h"
#include "../framework/GameConfig.h"
#include "Countdown.h"
#include "Scoreboard.h"
#include "WordsLabel.h"
#include "Player.h"

using namespace EasySDL;

class PlayScreen
{
public:

	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();
	void StartTurn();

private:

	Timer* mTimer;
	InputManager* mInputMgr;
	GameConfig* mGameConfig;

	bool mCanShoot;

	// Background
	Texture* mBackground;

	// Top Bar Scores
	Texture* mP1TextScore;
	Texture* mP1Label;
	Scoreboard* mP1Score;
	Texture* mP1Key;

	Texture* mP2TextScore;
	Texture* mP2Label;
	Scoreboard* mP2Score;
	Texture* mP2Key;

	// Countdown
	Countdown* mCountdown;

	// Bottom Bar Word
	WordsLabel* mWordsLabel;

	// Player 1
	Player* mPlayer1;

	// Player 2
	Player* mPlayer2;

};

#endif // _PLAYSCREEN_H
