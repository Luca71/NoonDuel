#include "Graphics.h"
#include "GameConfig.h"

namespace EasySDL
{
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;
	
	Graphics* Graphics::Instance()
	{
		if (sInstance == NULL)
		{
			sInstance = new Graphics();
		}
		return sInstance;
	}
	
	void Graphics::Release()
	{
		delete sInstance;
		sInstance = NULL;
	
		sInitialized = false;
	}
	
	bool Graphics::Initialized()
	{
		return sInitialized;
	}
	
	Graphics::Graphics()
	{
		mBackBuffer = nullptr;
	
		mGameConfig = GameConfig::Instance();
		sInitialized = Init();
	}
	
	Graphics::~Graphics()
	{
		GameConfig::Release();
		mGameConfig = nullptr;
		
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
	
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	
	bool Graphics::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			printf("SDL Initialization Error : %s\n", SDL_GetError());
			return false;
		}
	
		Uint32 flags = GameConfig::Instance()->isFullScreen == true ? SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
		
		mWindow = SDL_CreateWindow(mGameConfig->winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									mGameConfig->winWidth, mGameConfig->winHeight, flags);
	
		if (mWindow == NULL)
		{
			printf("Window Creation Error: %s\n", SDL_GetError());
			return false;
		}
	
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == NULL)
		{
			printf("Renderer Creation Error: %s\n", SDL_GetError());
			return false;
		}
	
		SDL_SetRenderDrawColor(mRenderer, COLOR_BLUE);
	
		int flag = IMG_INIT_PNG;
		if (!(IMG_Init(flag) & flag))
		{
			printf("IMG Initialization Error: %s\n", IMG_GetError());
			return false;
		}
	
		if (TTF_Init() == -1)
		{
			printf("TTF Initialization Error: %s\n", TTF_GetError());
			return false;
		}
	
		mBackBuffer = SDL_GetWindowSurface(mWindow);
	
		return true;
	}
	
	void Graphics::Render()
	{
		SDL_RenderPresent(mRenderer);
	}
	
	SDL_Texture* Graphics::LoadTexture(std::string path)
	{
		SDL_Texture* tex = nullptr;
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (surface == NULL)
		{
			printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
			return tex;
		}
	
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == NULL)
		{
			printf("Create Texture Error: %s)\n", SDL_GetError());
			return tex;
		}
	
		SDL_FreeSurface(surface);
	
		return tex;
	}
	
	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (surface == NULL)
		{
			printf("Text Render Error: %s", TTF_GetError());
			return NULL;
		}
		
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == NULL)
		{
			printf("Text Texture Creation Error: %s", SDL_GetError());
			return NULL;
		}
	
		SDL_FreeSurface(surface);
	
		return tex;
	}
	
	void Graphics::ClearBackBuffer()
	{
		SDL_RenderClear(mRenderer);
	}
	
	void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
	}
}
