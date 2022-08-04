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

	void EndTurn();
	void Reset();

private:

	Texture* mText;
	GameConfig* mGameConfig;
	Timer* mTimer;

	bool mCanShoot;
	bool mCanSwap;
	bool mIsTurnEnded;

	int mCount;
	std::vector<Texture*> mCountTexs;
	std::vector<std::string> mWords;

	Texture* mWordText;
	Texture* mWordLabel;
	Texture* mEndText1;
	Texture* mEndText2;
	Texture* mEndText3;

	int mCurrentWordIndex;
	int tempIndex;

	float mSwapTimer;
	float mSwapSpeed;

	void Stop();
	void ClearTexts();
	void ClearWords();

	void InitWords();
};

#endif // _WORDSLABEL_H
