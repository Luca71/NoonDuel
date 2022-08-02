#ifndef _ANIMATEDTEXTURE_H
#define _ANIMATEDTEXTURE_H
#include "Timer.h"
#include "Texture.h"

namespace EasySDL
{
	class AnimatedTexture : public Texture
	{
	public:
	
		enum WRAP_MODE { once = 0, loop = 1 };
		enum ANIM_DIR { horizontal = 0, vertical = 1 };
	
		/**
		 * Create animated texture from sprite sheet
		 * @param filename = The name of the texture file.
		 * @param x, y = The x and y value for the upper left corner of the file.
		 * @param w = The width of the single frame.
		 * @param h = The height of the single frame.
		 * @param frameCount = The total number of animation frame.
		 * @param animationSpeed = The speed of animation.
		 * @param animationDirection = If frames are aligned horizontally or vertically.
		 * @param flipped = Is the texture flipped horizontally
		 */
		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDirection, bool HFlipped = false, bool VFlipped = false);
		~AnimatedTexture();
	
		void WrapMode(WRAP_MODE mode);
		void Update();
	
	private:
	
		Timer* mTimer;
	
		int mStartX;
		int mStartY;
	
		float mAnimationTimer;
		float mAnimationSpeed;
		float mTimePerFrame;
	
		int mFrameCount;
	
		WRAP_MODE mWrapMode;
		ANIM_DIR mAnimationDirection;
	
		bool mAnimationDone;
	};
}


#endif // _ANIMATEDTEXTURE_H
