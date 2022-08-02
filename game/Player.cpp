#include "Player.h"

Player::Player(std::string idleTex, std::string shootTex, std::string deadTex, Vector2 position, bool flipped)
{
	mGameConfig = GameConfig::Instance();

	mCanShoot = true;

	// init state texture
	AnimatedTexture* temp = new AnimatedTexture(idleTex, 0, 0, 360, 360, 10, 0.5f, AnimatedTexture::horizontal, flipped);
	temp->Position(position);
	mStateTextures.push_back(temp);

	temp = new AnimatedTexture(shootTex, 0, 0, 360, 360, 5, 0.5f, AnimatedTexture::horizontal, flipped);
	temp->WrapMode(AnimatedTexture::once);
	temp->Position(position);
	mStateTextures.push_back(temp);

	temp = new AnimatedTexture(deadTex, 0, 0, 360, 360, 7, 0.5f, AnimatedTexture::horizontal, flipped);
	temp->WrapMode(AnimatedTexture::once);
	temp->Position(position);
	mStateTextures.push_back(temp);
	delete temp;

	mCurrentState = Idle;
	mPlayer = mStateTextures[mCurrentState];
}

Player::~Player()
{
	mStateTextures.clear();

	delete mPlayer;
	mPlayer = nullptr;
}

void Player::Update()
{
	mPlayer = mStateTextures[mCurrentState];
	
	mPlayer->Update();
}

void Player::Render()
{
	mPlayer = mStateTextures[mCurrentState];

	mPlayer->Render();
}

void Player::SetPosition(Vector2 pos)
{
	mPlayer->Position(pos);
}

void Player::SetState(PLAYER_STATE state)
{
	mCurrentState = state;
}

int Player::GetState()
{
    return mCurrentState;
}

void Player::CanShoot(bool canShoot)
{
	mCanShoot = canShoot;
}

bool Player::CanShoot()
{
	return mCanShoot;
}
