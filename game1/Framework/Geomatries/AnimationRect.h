#pragma once

#include "TextureRect.h"

class Animator;

class ShadedBuffer : public ShaderBuffer
{
public:
	ShadedBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.Selection = 0;
	}

	int * GetSelectionPtr() { return &data.Selection; }

	struct Data
	{
		int Selection;
		Vector3 dummy;
	};

private:
	Data data;
};

class AnimationRect : public TextureRect
{
public:
	AnimationRect(Vector3 position, Vector3 size);
	~AnimationRect();

	void Update();
	void Render();

	virtual void Move() override;

	void SetAnimation(Animator* animator) { this->animator = animator; }
	void SetCharacter(int _Character) { this->Character = _Character; }  //몬스터인지 캐릭터인지 투사체인지 설정해주는 함수
	void SetEnemy(int _enemyselection) { this->enemyselection = _enemyselection; }
	
	Vector3 targetpostiont = { 0,0,0 };

	//충돌관련함수

	BoundingBox* GetBox() { return box; }
	bool AABB(BoundingBox* other);

	//색변화함수
	void isDamaged(int i) { *(this->sb->GetSelectionPtr()) = i; }


	//캐릭터 기본 체력관련 함수
	int GetHp() { return Hp; }
	void SetHp(int _hp) { this->Hp = _hp; }

	void SetAttack(int _Attack) { this->Attack = _Attack; }
	int GetAttack() { return Attack; }

	int GetMaxHp() { return maxHp; }
	void SetMaxHp(int hp) { this->maxHp = hp; }

	bool GetisLive() { return isValid; }
	void SetisLive(bool a) { this->isValid = a; }


	//화살을 위한 방향
	int GetDirection() { return control->GetFacingWhere(); }
	void SetFacingWhere(int a) { this->_FacingWhere = a; }

	void SetclipName(wstring clipname1, wstring clipname2);//1 은 왼쪽방향 2 는 오른쪽방향



private:
	class Animator* animator = nullptr;
	class PControl* control = nullptr;
	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];
	
	int Character = 0; // 0 은 플레이어, 1 은 일반 몬스터, 2는 보스 몬스터, 3은 투사체, 4는 아이템

	//몬스터 전용 클립내임 이름바꾸기
	wstring clipNameL = L"idleL";
	wstring clipNameR = L"idleR";


	float KeyDown = 0.0f;
	float keyRate = 0.0f;
	float deltaTime = 0.0f;
	float Time = 0.0f;
	

	//화살의 방향을 위한 변수
	int _FacingWhere = 0;

	// position 관련 변수
	Vector3 beforeposition = { 0,0,0 };
	
	//hlsl 상수버퍼
	ShadedBuffer* sb = nullptr;

	bool isCollid = false;


	//enemy종류
	int enemyselection = 0;


	// 체력 데미지 죽었는지 
	int Hp = 100;
	int maxHp = 100;
	int Attack = 5;

	bool isValid = true;

	



};