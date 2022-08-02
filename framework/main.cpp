#include "GameManager.h"


int main(int argc, char** argv)
{
	EasySDL::GameManager* game = EasySDL::GameManager::Instance();

	game->Run();

	EasySDL::GameManager::Release();
	game = nullptr;

	return 0;
}