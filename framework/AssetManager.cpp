#include "AssetManager.h"

namespace EasySDL
{
	AssetManager* AssetManager::sInstance = nullptr;
	
	AssetManager* AssetManager::Instance()
	{
	    if (sInstance == NULL)
	    {
	        sInstance = new AssetManager();
	    }
	    return sInstance;
	}
	
	void AssetManager::Release()
	{
	    delete sInstance;
	    sInstance = nullptr;
	}
	
	SDL_Texture* AssetManager::GetTexture(std::string filename)
	{
	    std::string fullPath = SDL_GetBasePath();
	    fullPath.append("../../assets/" + filename);
	
	    if (mTextures[fullPath] == nullptr)
	    {
	        mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
	    }
	
	    return mTextures[fullPath];
	}
	
	AssetManager::AssetManager()
	{
	}
	
	AssetManager::~AssetManager()
	{
	    for (auto& tex : mTextures) // mTexture = std::map<std::string, SDL_Texture*>
	    {
			if (tex.second != NULL)
			{
				SDL_DestroyTexture(tex.second);
			}
	    }
	    mTextures.clear();
	
	    for (auto& text : mTexts)
	    {
	        if (text.second != NULL)
	        {
	            SDL_DestroyTexture(text.second);
	        }
	    }
	    mTexts.clear();
	
		for (auto& font : mFonts)
		{
			if (font.second != NULL)
			{
				TTF_CloseFont(font.second);
			}
		}
		mFonts.clear();
	
		for (auto& music : mMusic)
		{
			if (music.second != NULL)
			{
				Mix_FreeMusic(music.second);
			}
		}
		mMusic.clear();
	
		for (auto& chunk : mSFX)
		{
			if (chunk.second != NULL)
			{
				Mix_FreeChunk(chunk.second);
			}
		}
		mSFX.clear();
	}
	
	TTF_Font* AssetManager::GetFont(std::string filename, int size)
	{
	    std::string fullPath = SDL_GetBasePath();
	    fullPath.append("../../fonts/" + filename);
	    std::string key = fullPath + (char)size;
	
	    if (mFonts[key] == nullptr)
	    {
	        mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
	        if (mFonts[key] == nullptr)
	        {
	            printf("Font Loading Error: Fond-%s Error-%s\n", filename.c_str(), TTF_GetError());
	        }
	    }
	
	    return mFonts[key];
	}
	
	SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
	{
	    TTF_Font* font = GetFont(filename, size);
	
	    std::string key = text + filename + (char)size + (char)color.r + (char)color.g + (char)color.b + (char)color.a;
	
	    if (mTexts[key] == nullptr)
	    {
	        mTexts[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
	    }
	
	    return mTexts[key];
	}
	
	Mix_Music* AssetManager::GetMusic(std::string filename)
	{
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("../../audio/" + filename);
	
	    if (mMusic[fullPath] == nullptr)
	    {
	        mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
	        if (mMusic[fullPath] == NULL)
	        {
	            printf("Music Loading Error: File-%s Error-%s\n", filename.c_str(), Mix_GetError());
	        }
	    }
	    
	    return mMusic[fullPath];
	}
	
	Mix_Chunk* AssetManager::GetSFX(std::string filename)
	{
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("../../audio/" + filename);
	
		if (mSFX[fullPath] == nullptr)
		{
			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
			if (mSFX[fullPath] == NULL)
			{
				printf("SFX Loading Error: File-%s Error-%s\n", filename.c_str(), Mix_GetError());
			}
		}
	
		return mSFX[fullPath];
	}
}
