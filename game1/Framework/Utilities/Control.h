#pragma once

#include <Utilities/Animator.h>

class Control
{
public:
	Control();
	~Control();

	void Update();

	void Idle();

	void Right(DWORD key, Vector3* position, float speed, wstring clipName);
	void Left(DWORD key, Vector3* position, float speed, wstring clipName);
	void Up(DWORD key, Vector3* position, float speed, wstring clipName);
	void Down(DWORD key, Vector3* position, float speed, wstring clipName);
	void Jump(DWORD key, Vector3* position, float speed);

	void Attack(DWORD key);
	void Skill(DWORD key, DWORD key2);

	void SetAnimator(Animator** animator) { this->animator = animator; }

private:
	class Animator** animator = nullptr;

	bool FacingLeft = false;
	bool jump = false;

	float deltaTime = 0.0f;
	float keyDown = 0.0f;
	float KeyRate = 0.0f;
};
