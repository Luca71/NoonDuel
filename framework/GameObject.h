#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "GameManager.h"

namespace EasySDL
{
	class GameObject
	{
	public:
		
		virtual void Register() = 0;
		virtual void DeRegister() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}


#endif // _GAMEOBJECT_H
