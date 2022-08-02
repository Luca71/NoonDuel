#include "GameConfig.h"

namespace EasySDL
{
	GameConfig* GameConfig::sInstance = nullptr;
	
	GameConfig* GameConfig::Instance()
	{
		if (sInstance == NULL)
		{
			sInstance = new GameConfig();
		}
		return sInstance;
	}
	
	void GameConfig::Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}
	
	GameConfig::GameConfig()
	{
	}
	
	GameConfig::~GameConfig()
	{
	}
}
