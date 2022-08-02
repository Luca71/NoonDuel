#include "GameEntity.h"

namespace EasySDL
{
	GameEntity::GameEntity(Vector2 pos)
	{
		mPos = pos;
		mRotation = 0.0f;
		mActive = true;
		mParent = nullptr;
		mScale = VEC2_ONE;
	}
	
	GameEntity::~GameEntity()
	{
		mParent = nullptr;
	}
	
	void GameEntity::Position(Vector2 position)
	{
		mPos = position;
	}
	
	Vector2 GameEntity::Position(SPACE space /*= world*/)
	{
		if (space == local || mParent == nullptr) { return mPos; }
	
		Vector2 parentScale = mParent->Scale(world);
		//Vector2 rotPos = RotateVector(mPos, mParent->Rotation(local));
		Vector2 tmpPos = Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y);
		Vector2 rotPos = RotateVector(tmpPos, mParent->Rotation(local));
	
		return mParent->Position(world) + rotPos;
	}
	
	void GameEntity::Scale(Vector2 scale)
	{
		mScale = scale;
	}
	
	Vector2 GameEntity::Scale(SPACE space /*= world*/)
	{
		if (space == local || mParent == nullptr) { return mScale; }
		
		Vector2 scale = mParent->Scale(world);
		scale.x *= mScale.x;
		scale.y *= mScale.y;
	
		return scale;
	}
	
	void GameEntity::Rotation(float rotation)
	{
		mRotation = rotation;
		if (mRotation > 360.0f) { mRotation -= 360.0f; }
		if (mRotation < 0.0f) { mRotation += 360.0f; }
	}
	
	float GameEntity::Rotation(SPACE space /*= world*/)
	{
		if (space == local || mParent == nullptr) { return mRotation; }
		return mParent->Rotation(world) + mRotation;
	}
	
	void GameEntity::Active(bool active)
	{
		mActive = active;
	}
	
	bool GameEntity::Active()
	{
		return mActive;
	}
	
	void GameEntity::Parent(GameEntity* parent)
	{
		if (parent == NULL)
		{
			mPos = Position(world);
			mRotation = Rotation(world);
			mScale = Scale(world);
		}
		else
		{
			if (mParent != NULL)
			{
				Parent(NULL);
			}
	
			Vector2 parentScale = parent->Scale(world);
	
			Vector2 tmpPos = Position(world) - parent->Position(world);
			mPos = RotateVector(tmpPos, -parent->Rotation(world));
			mPos.x /= parentScale.x;
			mPos.y /= parentScale.y;
	
			mRotation -= parent->Rotation(world);
	
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}
		
		mParent = parent;
	}
	
	GameEntity* GameEntity::Parent()
	{
		return mParent;
	}
	
	void GameEntity::Translate(Vector2 vec)
	{
		mPos += vec;
	}
	
	void GameEntity::Rotate(float amount)
	{
		mRotation += amount;
	}
	
	void GameEntity::Update()
	{
	}
	
	void GameEntity::Render()
	{
	}
}

