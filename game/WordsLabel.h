#ifndef _WORDSLABEL_H
#define _WORDSLABEL_H
#include "../framework/Texture.h"
#include "../framework/GameConfig.h"
#include "../framework/Timer.h"
#include <vector>

using namespace EasySDL;

class WordsLabel : public GameEntity
{
public:

	WordsLabel();
	~WordsLabel();

	void Start();
	void Update();
	void Render();

	bool CanShoot();
	void CanShoot(bool canShoot);

	enum ENDTURN_STATE { none, win, loose, winGame };

	void SetEndTurnState(ENDTURN_STATE state);
	void Reset();

private:

	Texture* mText;
	GameConfig* mGameConfig;
	Timer* mTimer;

	bool mCanShoot;
	bool mCanSwap;

	ENDTURN_STATE mEndTurnState;

	int mCount;
	std::vector<Texture*> mCountTexs;
	std::vector<std::string> mWords;

	Texture* mWordText;
	Texture* mWordLabel;

	Texture* mEndTextFailed;
	Texture* mEndTextWin;

	Texture* mPlayerWinGame;

	Texture* mEndTextLoosePoint;
	Texture* mEndTextEarnPoint;

	Texture* mEndTextRestart;
	Texture* mWinTextRestart;

	int mCurrentWordIndex;
	int tempIndex;

	float mSwapTimer;
	float mSwapSpeed;

	void Stop();
	void ClearTexts();
	void ClearWords();
	void LooseTurn();
	void WinTurn();
	void WinGame();

	void InitWords();
};

#endif // _WORDSLABEL_H
