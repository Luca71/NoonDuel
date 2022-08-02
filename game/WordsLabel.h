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

private:

	Texture* mText;
	GameConfig* mGameConfig;
	Timer* mTimer;

	bool mCanShoot;

	int mCount;
	std::vector<Texture*> mCountTexs;
	std::vector<std::string> mWords;

	Texture* mWordText;
	Texture* mWordLabel;

	int mCurrentWordIndex;
	int tempIndex;

	float mSwapTimer;
	float mSwapSpeed;

	void Reset();
	void Stop();
	void ClearTexts();
	void ClearWords();

	void InitWords();
};

#endif // _WORDSLABEL_H
