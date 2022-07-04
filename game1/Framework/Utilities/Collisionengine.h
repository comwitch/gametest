#pragma once

#include <Utilities/Animator.h>

struct boxdata
{
	
	BoundingBox* box;
	Vector3* position;
	Vector3 velocity;
	class AnimationRect * AnimRect;
	int checker;
};



class Collisionengine
{

public:
	Collisionengine();
	~Collisionengine();


	// tik�� �Ͼ�� �Լ���
	void Update();
	void UpdateCollision();



	//�浹 ���� �Լ� �� ����Ǿ��� �� 
	bool AABB(boxdata* A, boxdata* B);
	void CollisionEffect(boxdata* A, boxdata* B);
	void CollisionOverlaps(boxdata* A, boxdata* B);


	void UpdateVelocity();


	//����� �� �� Ȯ��
	int GetEnemycount() { return enemycount; }
	void SetEnemycount(int count) { this->enemycount = count; }
	
	//�� ����ü�� �԰ݹ�, ��������� �������� �����ؼ� �������� ���� ���.
	void insert(BoundingBox* box, Vector3* position, AnimationRect* AnimRect, int checker);
	void erase(Vector3* position);
	void clean();



private:

	/*
	Boxes : �־��� �԰��� ������ ����
	Positions : �־��� ��ġ�� ����
	Velocities : ����� �ؼ� ���� ������Ʈ�� �ӵ��� ����.
	checkers : �־��� �繰�� �÷��̾�� ĳ��������, ȭ������, �������� �Ǵ�
	*/


	vector<Vector3*> Positions;
	vector<Vector3> tmpPositions;
	vector<boxdata*> datas;
	Vector3 Position;
	int count = -1;

	int enemycount;
	



	float realTime = 0.0f;
	float checkerTime = 0.0f;

};