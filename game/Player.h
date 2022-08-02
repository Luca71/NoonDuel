#ifndef _PLAYER_H
#define _PLAYER_H
#include "../framework/AnimatedTexture.h"
#include "../framework/GameConfig.h"
#include <vector>;

using namespace EasySDL;

class Player : public GameEntity
{
public:

	Player( std::string idleTex, std::string shootTex, std::string deadTex, Vector2 position, bool flipped = false );
	~Player();

	void Update();
	void Render();
	
	enum PLAYER_STATE { Idle, Shoot, Dead };

	void SetPosition(Vector2 pos);
	void SetState(PLAYER_STATE state);
	int GetState();

	void CanShoot(bool canShoot);
	bool CanShoot();

private:

	PLAYER_STATE mCurrentState;

	AnimatedTexture* mPlayer;
	GameConfig* mGameConfig;

	bool mCanShoot;

	std::vector<AnimatedTexture*> mStateTextures;

	void ClearStateTextures();
};


#endif // _PLAYER_H
