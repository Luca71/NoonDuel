#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	mGameConfig = GameConfig::Instance();
	Score(0);
}

Scoreboard::~Scoreboard()
{
	GameConfig::Release();
	mGameConfig = nullptr;

	ClearBoard();
}

void Scoreboard::Score(int score)
{
	ClearBoard();
	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", mGameConfig->secondFont, mGameConfig->ScoreFontSize, { COLOR_DARKBROWN }));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(-36.0f * i, 0.0f));
		}
	}
	else
	{
		std::string str = std::to_string(score);
		int lastIndex = str.length();

		for (int i = 0; i < lastIndex; i++)
		{
			mScore.push_back(new Texture(str.substr(i, 1), mGameConfig->secondFont, mGameConfig->ScoreFontSize, { COLOR_DARKBROWN }));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(-36.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Scoreboard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}

void Scoreboard::ClearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = nullptr;
	}
	mScore.clear();
}