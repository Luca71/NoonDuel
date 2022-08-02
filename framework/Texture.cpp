#include "Texture.h"

namespace EasySDL
{
	Texture::Texture(std::string filename, bool HFlipped, bool VFlipped)
	{
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename);
	
		SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	
		mClipped = false;
		mHFlipped = HFlipped;
		mVFlipped = VFlipped;
	
		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;
	}
	
	Texture::Texture(std::string filename, int x, int y, int w, int h, bool HFlipped, bool VFlipped)
	{
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename);
	
		mClipped = true;
		mHFlipped = HFlipped;
		mVFlipped = VFlipped;
	
		mWidth = w;
		mHeight = h;
	
		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;
	
		mClipRect.x = x;
		mClipRect.y = y;
		mClipRect.w = mWidth;
		mClipRect.h = mHeight;
	}
	
	Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
	{
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);
	
		mClipped = false;
	
		SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	
		mRenderRect.w = mWidth;
		mRenderRect.h = mHeight;
	}
	
	Texture::~Texture()
	{
		mTex = nullptr;
		mGraphics = nullptr;
	}
	
	void Texture::Render()
	{
		Vector2 pos = Position(world);
		Vector2 scale = Scale(world);
	
		mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
		mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
		mRenderRect.w = (int)(mWidth * scale.x);
		mRenderRect.h = (int)(mHeight * scale.y);

	
		//mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(world), (mFlipped) ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
		mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(world), FlipTexture());
	}

	SDL_RendererFlip Texture::FlipTexture()
	{
		int flip = SDL_FLIP_NONE;

		if (mHFlipped)
		{
			flip += SDL_FLIP_HORIZONTAL;
		}
		if (mVFlipped)
		{
			flip += SDL_FLIP_VERTICAL;
		}

		return (SDL_RendererFlip)(flip);
	}
}


