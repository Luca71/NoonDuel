#include "InputManager.h"

namespace EasySDL
{
	InputManager* InputManager::sInstance = nullptr;
	
	
	InputManager* InputManager::Instance()
	{
	    if (sInstance == NULL)
	    {
	        sInstance = new InputManager();
	    }
	    return sInstance;
	}
	
	void InputManager::Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}
	
	
	InputManager::InputManager() : mMouseXPos(0), mMouseYPos(0)
	{
		mKeyboardState = SDL_GetKeyboardState(&mKeyLenght);
	    mPrevKeyboardState = new Uint8[mKeyLenght];
	    memcpy(mPrevKeyboardState, mKeyboardState, mKeyLenght);
	
		mPrevMouseState = 0;
		mMouseState = 0;
	}
	
	InputManager::~InputManager()
	{
	    delete[] mPrevKeyboardState;
	    mPrevKeyboardState = nullptr;
	}
	
	
	bool InputManager::KeyDown(SDL_Scancode scanCode)
	{
	    return mKeyboardState[scanCode];
	}
	
	bool InputManager::KeyPressed(SDL_Scancode scanCode)
	{
	    return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
	}
	
	bool InputManager::KeyReleased(SDL_Scancode scanCode)
	{
		return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];
	}
	
	bool InputManager::MouseButtonDown(MOUSE_BUTTON button)
	{
	    Uint32 mask = 0;
	
	    switch (button)
	    {
	    case mouseLeft:
	
	        mask = SDL_BUTTON_LMASK;
	        break;
	
		case mouseRight:
	
			mask = SDL_BUTTON_RMASK;
			break;
	
		case mouseMiddle:
	
			mask = SDL_BUTTON_MMASK;
			break;
	
		case mouseBack:
	
			mask = SDL_BUTTON_X1;
			break;
	
		case mouseForward:
	
			mask = SDL_BUTTON_X2;
			break;
	    }
	
	    return (mMouseState & mask);
	}
	
	bool InputManager::MouseButtonPressed(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;
	
		switch (button)
		{
		case mouseLeft:
	
			mask = SDL_BUTTON_LMASK;
			break;
	
		case mouseRight:
	
			mask = SDL_BUTTON_RMASK;
			break;
	
		case mouseMiddle:
	
			mask = SDL_BUTTON_MMASK;
			break;
	
		case mouseBack:
	
			mask = SDL_BUTTON_X1;
			break;
	
		case mouseForward:
	
			mask = SDL_BUTTON_X2;
			break;
		}
	
		return !(mPrevMouseState & mask) && (mMouseState & mask);
	}
	
	bool InputManager::MouseButtonReleased(MOUSE_BUTTON button)
	{
		Uint32 mask = 0;
	
		switch (button)
		{
		case mouseLeft:
	
			mask = SDL_BUTTON_LMASK;
			break;
	
		case mouseRight:
	
			mask = SDL_BUTTON_RMASK;
			break;
	
		case mouseMiddle:
	
			mask = SDL_BUTTON_MMASK;
			break;
	
		case mouseBack:
	
			mask = SDL_BUTTON_X1;
			break;
	
		case mouseForward:
	
			mask = SDL_BUTTON_X2;
			break;
		}
	
		return (mPrevMouseState & mask) && !(mMouseState & mask);
	}
	
	Vector2 InputManager::MousePos()
	{
	    return Vector2((float)mMouseXPos, (float)mMouseYPos);
	}
	
	void InputManager::Update()
	{
		mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
	}
	
	void InputManager::UpdatePrevInput()
	{
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLenght);
		mPrevMouseState = mMouseState;
	}
}
