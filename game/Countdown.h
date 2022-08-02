#ifndef _COUNTDOWN_H
#define _COUNTDOWN_H
#include "../framework/Texture.h"
#include "../framework/GameConfig.h"
#include "../framework/Timer.h"

#include <vector>

using namespace EasySDL;

class Countdown : public GameEntity
{
public:

	Countdown();
	~Countdown();

	void Start();
	void Update();
	void Render();

private:

	Texture* mText;
	GameConfig* mGameConfig;
	Timer* mTimer;

	int mCount;
	std::vector<Texture*> mCountTexs;

	float mSwapTimer;
	float mSwapSpeed;

	void Reset();
	void ClearTexts();
};

#endif // _COUNTDOWN_H
