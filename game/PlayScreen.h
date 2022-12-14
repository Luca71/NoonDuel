#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "../framework/AnimatedTexture.h"
#include "../framework/InputManager.h"
#include "../framework/AudioManager.h"
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
	void EndTurn(bool win);
	void NewGame();

	void PlayMusic();

	enum TURN_STATE { start, running, end, winGame };
	int GetState();

private:

	Timer* mTimer;
	InputManager* mInputMgr;
	AudioManager* mAudioMgr;
	GameConfig* mGameConfig;

	bool mCanShoot;

	TURN_STATE mCurrentTurnState;

	void OnMatchWin(Player* player);
	bool CheckPlayersScore();

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

	// Player 1 fails
	std::vector<Texture*> mP1Fails;

	// Player 2 fails
	std::vector<Texture*> mP2Fails;
};

#endif // _PLAYSCREEN_H
