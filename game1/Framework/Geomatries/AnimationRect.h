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

	Animator** GetAnimator() { return &animator; }
	Vector3* GetPosition() { return &position; }

private:
	class Animator* animator = nullptr;
	class Control* control = nullptr;
	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];

	float KeyDown = 0.0f;
	float keyRate = 0.0f;
	float deltaTime = 0.0f;

	float jump = 0.0f;
	float timeChecker = 0.0f;
	bool FacingLeft = false;
	bool JumpFlags = false;
};