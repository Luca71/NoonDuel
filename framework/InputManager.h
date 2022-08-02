#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <SDL.h>
#include <string.h>
#include "MathHelper.h"

namespace EasySDL
{
	class InputManager
	{
	public:
	
		static InputManager* Instance();
		static void Release();
	
		bool KeyDown(SDL_Scancode scanCode);
		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);
	
		enum MOUSE_BUTTON { mouseLeft = 0, mouseRight, mouseMiddle, mouseBack, mouseForward };
		bool MouseButtonDown(MOUSE_BUTTON button);
		bool MouseButtonPressed(MOUSE_BUTTON button);
		bool MouseButtonReleased(MOUSE_BUTTON button);
	
		Vector2 MousePos();
	
		void Update();
		void UpdatePrevInput();
	
	private:
	
		static InputManager* sInstance;
	
		InputManager();
		~InputManager();
	
		Uint8* mPrevKeyboardState;
		const Uint8* mKeyboardState;
		int mKeyLenght;
	
		Uint32 mPrevMouseState;
		Uint32 mMouseState;
	
		int mMouseXPos;
		int mMouseYPos;
	};
}


#endif // _INPUTMANAGER_H
