#pragma once

#include "TextureRect.h"

class Animator;
class AnimationRect : public TextureRect
{
public:
	AnimationRect(Vector3 position, Vector3 size);
	~AnimationRect();

	void Update();
	void Render();

	virtual void Move() override;
	void SetAnimation(Animator* animator) { this->animator = animator; }

private:
	class Animator* animator = nullptr;
	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];
	float KeyDown = 0.0f;
	float KeyDown2 = 0.0f;
	bool FacingLeft = false;
	float Jump = 0.0f;
	float deltatime2 = 10.0f;
	float timeChecker = 0.0f;
	bool JumpFlag = 0;
};