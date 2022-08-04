#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H
#include "../framework/Texture.h"
#include "../framework/GameConfig.h"
#include <vector>

using namespace EasySDL;

class Scoreboard : public GameEntity
{
public:

	Scoreboard();
	~Scoreboard();

	void Score(int score);
	void Render();

	int GetScore();
	void IncrementScore();
	void ResetScore();

private:

	std::vector<Texture*> mScore;
	GameConfig* mGameConfig;

	int mCurrentScore;

	void ClearBoard();
};


#endif // _SCOREBOARD_H
