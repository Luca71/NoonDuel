#ifndef _GAMECONFIG_H
#define _GAMECONFIG_H
#include <string>


namespace EasySDL
{
	#define COLOR_RED		255, 0, 0, 255
	#define COLOR_GREEN		0, 255, 0, 255
	#define COLOR_BLUE		0, 0, 255, 255
	#define COLOR_BLACK		0, 0, 0, 255
	#define COLOR_DARKBROWN	127, 79, 0, 255
	#define COLOR_GRAY		96, 96, 96, 255
	#define COLOR_DARKRED	159, 8, 0, 255

	class GameConfig
	{
		
	public:
	
		static GameConfig* Instance();
		static void Release();
	
		const int winWidth = 1280;
		const int winHeight = 720;
		const std::string winTitle = "NOON DUEL";
		const std::string mainFont = "DSRoundup.ttf";
		const std::string secondFont = "edmunds.ttf";
		const int ScoreFontSize = 50;
		const int TextScoreFontSize = 40;
		const int CounterFontSize = 200;
		const int WordsFontSize = 80;
		const bool isFullScreen = false;

		const int ShootWordsMaxCount = 5;
		const int MaxScoreToWin = 5;
	
	private:
	
		GameConfig();
		~GameConfig();
		static GameConfig* sInstance;
	};
}

#endif // _GAMECONFIG_H
