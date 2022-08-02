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

private:

	std::vector<Texture*> mScore;
	GameConfig* mGameConfig;

	void ClearBoard();
};


#endif // _SCOREBOARD_H
