#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameEntity.h"
#include "AssetManager.h"

namespace EasySDL
{
	class Texture : public GameEntity
	{
	public:
	
		/**
		 * Create a texture from a file with origin width and height.
		 * @param filename = The name of the texture.
		 * @param bool flipped = Is the texture flipped horizontally. Default = false.
		 */
		Texture(std::string filename, bool HFlipped = false, bool VFlipped = false);
	
		/**
		 * Create clipped texture.
		 * @param int x, y = The x and y value for the upper left corner of the file.
		 * @param int w = The width of the clipped texture.
		 * @param int h = The height of the clipped texture.
		 * @param bool flipped = Is the texture flipped horizontally. Default = false.
		 */
		Texture(std::string filename, int x, int y, int w, int h, bool HFlipped = false, bool VFlipped = false);
	
		/**
		 * Create a text texture from a given font
		 * @param text The text message
		 * @param fontPath The name of the font (e.g.: "serif.ttf")
		 * @param color The color of the font 
		 */
		Texture(std::string text, std::string fontPath, int size, SDL_Color color);
		~Texture();
	
		virtual void Render();
	
	protected:
	
		SDL_Texture* mTex;
		Graphics* mGraphics;
	
		int mWidth;
		int mHeight;
	
		bool mClipped;
		bool mHFlipped;
		bool mVFlipped;

		SDL_Rect mRenderRect;
		SDL_Rect mClipRect;

		SDL_RendererFlip FlipTexture();
	};
}


#endif // _TEXTURE_H
