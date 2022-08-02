#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "../framework/GameConfig.h"

namespace EasySDL
{
	class Graphics
	{
	public:
	
		//static const int SCREEN_WIDTH = 800;
		//static const int SCREEN_HEIGHT = 600;
	
		static Graphics* Instance();
		static void Release();
		static bool Initialized();
		void Render();
	
		SDL_Texture* LoadTexture(std::string path);
		void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
	
		void ClearBackBuffer();
	
	private:
	
		Graphics();
		~Graphics();
	
		bool Init();
	
		static Graphics* sInstance;
		static bool sInitialized;
		SDL_Window* mWindow;
		SDL_Surface* mBackBuffer;
		SDL_Renderer* mRenderer;
		GameConfig* mGameConfig;
	};
}



#endif // _GRAPHICS_H
