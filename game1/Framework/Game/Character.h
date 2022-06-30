#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

class Character
{
public:
	Character(Vector3 position, Vector3 size);
	virtual ~Character();

	virtual void Update() = 0;
	virtual void Render() = 0;
	Vector3* GetPosition();
	void SetCollision(float LT_x, float LT_y, float RB_x, float RB_y);
	

protected:
	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;
};