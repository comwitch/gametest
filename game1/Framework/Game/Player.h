#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player(Vector3 position, Vector3 size);
	~Player();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	
	class Control* control = nullptr;

	AnimationRect* GetAnim() { return animRect; }
};