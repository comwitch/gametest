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
	void SetCharacter(int _Character) { this->Character = _Character; }  //�������� ĳ�������� ����ü���� �������ִ� �Լ�

	
	Vector3 targetpostiont = { 0,0,0 };

	//�浹�����Լ�

	BoundingBox* GetBox() { return box; }
	bool AABB(BoundingBox* other);

	//����ȭ�Լ�
	void isDamaged(int i) { *(this->sb->GetSelectionPtr()) = i; }


	//ĳ���� �⺻ ü�°��� �Լ�
	int GetHp() { return Hp; }
	void SetHp(int _hp) { this->Hp = _hp; }

	void SetAttack(int _Attack) { this->Attack = _Attack; }
	int GetAttack() { return Attack; }

	bool GetisLive() { return isValid; }
	void SetisLive(bool a) { this->isValid = a; }



private:
	class Animator* animator = nullptr;
	class PControl* control = nullptr;
	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];
	
	int Character = 0; // 0 �� �÷��̾�, 1 �� �Ϲ� ����, 2�� ���� ����, 3�� ����ü

	
	float KeyDown = 0.0f;
	float keyRate = 0.0f;
	float deltaTime = 0.0f;
	float Time = 0.0f;
	

	//ȭ���� ������ ���� ����
	int _FacingWhere = 0;

	// position ���� ����
	Vector3 beforeposition = { 0,0,0 };
	
	ShadedBuffer* sb = nullptr;

	bool isCollid = false;



	// ü�� ������ �׾����� 
	int Hp = 100;
	int Attack = 5;

	bool isValid = true;

	



};