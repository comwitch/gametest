#pragma once

#include <Utilities/Animator.h>

static int* checker;
 


class PControl
{
public:
	PControl();
	~PControl();

	void Update();

	void Idle();

	// character control
	void Right(DWORD key, Vector3* position, float speed, wstring clipName);
	void Left(DWORD key, Vector3* position, float speed, wstring clipName);
	void Up(DWORD key, Vector3* position, float speed, wstring clipName);
	void Down(DWORD key, Vector3* position, float speed, wstring clipName);


	int GetFacingWhere() { return FacingWhere; }
	void SetFacingWhere(int i) { FacingWhere = i; }


	void Attack(DWORD key);
	void Skill(DWORD key, DWORD key2);
	
	
	// enemy control
	void move(Vector3* position, Vector3* targetPosition, float speed);

	


	// arrow control
	//void ArrowUp(DWORD key, Vector3* position, float speed);
	void ArrowRight(DWORD key, Vector3* position, float speed, int _FacingWhere);



	//normal control ( 충돌 후 반응을 위해 사용할 함수)
	void collision(Vector3* position, float speedx, float speedy);

	void SetAnimator(Animator** animator) { this->animator = animator; }
	int GetSkill() { return _Skill; }

	

private:
	class Animator** animator = nullptr;

	
	
	
	bool FacingLeft = false;
	bool FacingUp = false;
	bool UDCheck = false;
	bool jump = false;
	bool attack = false;


	int _Skill = 4; //0 is left, 1 is right, 2 is Up, 3 is Down, 4 is notshooting
	int tmp_Face = 0;
	
	int FacingWhere = 1; //0 is Left , 1 is Right , 2 is Up, 3 is Down 


	float deltaTime = 0.0f;
	float keyDown = 0.0f;
	float checker = 0.0f;
};
