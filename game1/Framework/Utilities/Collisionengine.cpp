#include "Framework.h"
#include "Collisionengine.h"
#include "Systems/GData.h"
#include "Game/Character.h"
#include "Geomatries/AnimationRect.h"

Collisionengine::Collisionengine()
{
	realTime = 0.0f;
	checkerTime = 0.0f;
}

Collisionengine::~Collisionengine()
{
	
}

void Collisionengine::Update()
{

	
	realTime += Time::Delta();
	checkerTime += Time::Delta();
	

	UpdateCollision();
	UpdateVelocity();
	

	
	
	//���� �ӵ� ����� ���� ���� ��ġ�� ����.
	vector<Vector3*>::iterator iter2 = Positions.begin();
	vector<Vector3>::iterator iter3 = tmpPositions.begin();
	for (; iter2 != Positions.end(); iter2++)
	{
		(*iter3).x = (**iter2).x;
		(*iter3).y = (**iter2).y;
		(*iter3).z = (**iter2).z;
		

		iter3++;
	}

}

void Collisionengine::UpdateCollision()
{
	vector<boxdata*>::iterator iter = datas.begin();
	vector<boxdata*>::iterator iter2;
	for (; iter != datas.end(); iter++)
	{
		for (iter2 = iter + 1; iter2 != datas.end(); iter2++)
		{
			
			AABB((*iter), (*iter2));
		
		}
	}

}





// �浹�� �Ͼ �ൿ���� �����ϴºκ�

bool Collisionengine::AABB(boxdata * A, boxdata * B)
{
	if (A->box->AABB(B->box) == true)
	{
		// �ӵ��� �̿��� �浹
		//CollisionEffect(A, B);

		// ��ġ�� �κ��� �̿��� �浹
		if(A->checker == 2 && B->checker == 2 && A->AnimRect->GetisLive() == true && B->AnimRect->GetisLive() == true)
			CollisionOverlaps(A, B);



		/*
		ĳ���Ϳ� ���Ͱ� �浹���� �� �Ͼ�� ���� 
		1. ĳ������ HP�� 10��ŭ ���̰� �װ��� hp���¹ٿ� ������ �Ѱ���.
		2. ĳ���Ϳ� IsDamaged�Լ��� ���ؼ� �ȼ����̴��� ���� �ٲ���(ĳ���Ͱ� �����̴� ȿ��)
		
		*/
		if (A->checker == 1 && B->checker == 2 && checkerTime > 1.0f)
		{
			if (A->AnimRect->GetHp() > 0 && B->AnimRect->GetisLive() == true)
			{
				A->AnimRect->SetHp(A->AnimRect->GetHp() - 10);
				checkerTime = 0;
				A->AnimRect->isDamaged(1);
			}	
		}
		if (B->checker == 1 && A->checker==2 && checkerTime > 1.0f)
		{
			if (B->AnimRect->GetHp() > 0)
			{
				B->AnimRect->SetHp(B->AnimRect->GetHp() - 10);
				checkerTime = 0;
				B->AnimRect->isDamaged(1);
			}	
		}

		if (A->checker == 3 && B->checker == 2 && A->AnimRect->GetisLive() == true && B->AnimRect->GetisLive() == true)
		{
			if (B->AnimRect->GetHp() > 0)
			{
				B->AnimRect->SetHp(B->AnimRect->GetHp() - 50);
				A->AnimRect->SetisLive(false);

			}
			else
			{
				A->AnimRect->SetisLive(false);
				B->AnimRect->SetisLive(false);
			}
		}
		
		
		return true;
	}
	else
	{
		//�浹���� ������ �ٽ� ������� ��������
		A->AnimRect->isDamaged(0);
		B->AnimRect->isDamaged(0);
		
		return false;
	}
	
}

//�浹 �� ���� 1. �ӵ� ����

void Collisionengine::CollisionEffect(boxdata * A, boxdata * B)
{
	/*
	tmpAxis : �� ��ü�� �߽��� �����س��� ���� �Ŀ� ����ȭ�� ���Ѽ� �������ͷ� ����ϰԵȴ�
	normalizedtmpAxis : ũ�Ⱑ 1�� ��������
	normalizedtmpAxis_normalVector : ���� ���͸� 90���� ȸ����ȯ ��Ų ����

	Dotproduct_A, Dotproduct_B : A, B�� �ӵ����Ϳ� normalizedtmpAxis���� ������ 

	Dotproduct_A_normalvector, Dotproduct_B_normalvector A, B�� �ӵ����Ϳ� normalizedtmpAxis_normalVector ���� ������

	AbsSum, AbsSum_normalvector : �� ��� ������ ������ �������ͷ� ����� ����

	
	*/
	Vector3 tmpAxis = (*(*A).position) -(*(*B).position);
	float normalize = sqrt((tmpAxis.x)*(tmpAxis.x) + (tmpAxis.y)*(tmpAxis.y));
	

	Vector3 normalizedtmpAxis = tmpAxis / normalize;
	// 2���� �󿡼��� normal vector�� ���ϴ� ����� ���� ���Ϳ��� 90�� 2���� ȸ����ȯ�� ���ָ� �ȴ�.
	Vector3 normalizedtmpAxis_normalVector = Vector3((-1)*normalizedtmpAxis.y, normalizedtmpAxis.x, normalizedtmpAxis.z);

	float Dotproduct_A = D3DXVec3Dot(&normalizedtmpAxis, &(*A).velocity);
	float Dotproduct_B = D3DXVec3Dot(&normalizedtmpAxis, &(*B).velocity);

	float Dotproduct_A_normalvector = D3DXVec3Dot(&normalizedtmpAxis_normalVector, &(*A).velocity);
	float Dotproduct_B_normalvector = D3DXVec3Dot(&normalizedtmpAxis_normalVector, &(*B).velocity);


	float AbsSum = abs(Dotproduct_A) + abs(Dotproduct_B);
	float AbsSum_normalvector = abs(Dotproduct_A_normalvector) + abs(Dotproduct_B_normalvector);
	
	if (((AbsSum)*normalizedtmpAxis.x)*(Time::Delta()) < 5 && ((AbsSum)*normalizedtmpAxis.y)*(Time::Delta()) < 5)
	{
		(*(*B).position) = (*(*B).position) - (Time::Delta())*(*B).velocity - 0.5*(Time::Delta())*(AbsSum)*normalizedtmpAxis - 0.5*(Time::Delta())*(AbsSum_normalvector)*normalizedtmpAxis_normalVector;
		(*(*A).position) = (*(*A).position) - (Time::Delta())*(*A).velocity + 0.5*(Time::Delta())*(AbsSum)*normalizedtmpAxis + 0.5*(Time::Delta())*(AbsSum_normalvector)*normalizedtmpAxis_normalVector;
	}
	else
	{
		(*(*B).position) = (*(*B).position) - (Time::Delta())*(*B).velocity - 0.5*(Time::Delta())*(5)*normalizedtmpAxis - 0.5*(Time::Delta())*(5)*normalizedtmpAxis_normalVector;
		(*(*A).position) = (*(*A).position)- (Time::Delta())*(*A).velocity + 0.5*(Time::Delta())*(5)*normalizedtmpAxis + 0.5*(Time::Delta())*(5)*normalizedtmpAxis_normalVector;
	}	
}

// �浹 �� ���� 2. overlap�Ǵºκи� ��������

void Collisionengine::CollisionOverlaps(boxdata * A, boxdata * B)
{

	/*
	tmpAxis : �� ��ü�� �߽��� �����س��� ���� �Ŀ� ����ȭ�� ���Ѽ� �������ͷ� ����ϰԵȴ�
	normalizedtmpAxis : ũ�Ⱑ 1�� ��������
	normalizedtmpAxis_normalVector : ���� ���͸� 90���� ȸ����ȯ ��Ų ����

	Overlapdata : ��ģ �κ��� vector3�� ǥ��


	*/
	
	Vector3 tmpAxis = (*(*A).position) - (*(*B).position);
	float normalize = sqrt((tmpAxis.x)*(tmpAxis.x) + (tmpAxis.y)*(tmpAxis.y));
	Vector3 normalizedtmpAxis = tmpAxis / normalize;
	// 2���� �󿡼��� normal vector�� ���ϴ� ����� ���� ���Ϳ��� 90�� ȸ����ȯ�� ���ָ� �ȴ�.
	Vector3 normalizedtmpAxis_normalVector = Vector3((-1)*normalizedtmpAxis.y, normalizedtmpAxis.x, normalizedtmpAxis.z);

	Vector3 Overlapdata = { 0,0,0 };

	if (((*A).box->GetEdge()->RB.x - (*B).box->GetEdge()->LT.x) < ((*B).box->GetEdge()->RB.x - (*A).box->GetEdge()->LT.x))
	{
		Overlapdata.x = ((*A).box->GetEdge()->RB.x - (*B).box->GetEdge()->LT.x);
	}
	else
	{
		Overlapdata.x = ((*B).box->GetEdge()->RB.x - (*A).box->GetEdge()->LT.x);
	}

	if (((*A).box->GetEdge()->LT.y - (*B).box->GetEdge()->RB.y) < ((*B).box->GetEdge()->LT.y - (*A).box->GetEdge()->RB.y))
	{
		Overlapdata.y = ((*A).box->GetEdge()->LT.y - (*B).box->GetEdge()->RB.y);
	}
	else
	{
		Overlapdata.y = ((*B).box->GetEdge()->LT.y - (*A).box->GetEdge()->RB.y);
	}

	
	float Overlapsize = sqrt((Overlapdata.x)*(Overlapdata.x) + (Overlapdata.y)*(Overlapdata.y));

	(*(*B).position) = (*(*B).position) - 0.1*(Overlapsize)*normalizedtmpAxis - 0.1*(Overlapsize)*normalizedtmpAxis_normalVector;
	(*(*A).position) = (*(*A).position) + 0.1*(Overlapsize)*normalizedtmpAxis + 0.1*(Overlapsize)*normalizedtmpAxis_normalVector;

	


}





// �ӵ��� ������Ʈ�ϴ� �κ�

void Collisionengine::UpdateVelocity()
{
	vector<boxdata*>::iterator iter = datas.begin();
	vector<Vector3*>::iterator iter2 = Positions.begin();
	vector<Vector3>::iterator iter3 = tmpPositions.begin();
	for (; iter != datas.end(); iter++)
	{
		float vel_X = ((*iter2)->x - (*iter3).x)/Time::Delta() ;
		float vel_Y = ((*iter2)->y - (*iter3).y)/Time::Delta();

		(*iter)->velocity.x = vel_X;
		(*iter)->velocity.y = vel_Y;
		(*iter)->velocity.z = 0;
		


		iter2++;
		iter3++;
	}
}

//������Ʈ�� �޾Ƶ��̴� �κ�

void Collisionengine::insert(BoundingBox * box, Vector3 * position,AnimationRect* AnimRect, int checker)
{
	
	datas.push_back(new boxdata());
	count++;
	datas[count]->box = box;
	datas[count]->position = position;
	datas[count]->checker = checker;
	datas[count]->velocity = {0.0f, 0.0f, 0.0f };
	datas[count]->AnimRect = AnimRect;
	
	this->Position = *position;

	

	Positions.push_back(position);
	
	
	tmpPositions.push_back({ 0,0,0 });


}

//�ڽ��������� ���Ϳ��� Ư�� ������Ʈ�� position�� ���ؼ� ����� �κ�.

void Collisionengine::erase(Vector3 * position)
{
	vector<boxdata*>::iterator iter = datas.begin();
	for (; iter != datas.end(); iter++)
	{
		if ((*iter)->position == position)
		{
			delete (*iter);
			iter = datas.erase(iter);
		}
	}
	vector<Vector3*>::iterator iter2 = (Positions.begin());
	vector<Vector3>::iterator iter3 = tmpPositions.begin();
	for (; iter2 != Positions.end(); iter2++)
	{
		if (*iter2 == position)
		{
			delete (*iter2);
			iter2 = Positions.erase(iter2);
			delete (*iter3);
			iter3 = tmpPositions.erase(iter3);
		}
		else
		{
			iter3++;
		}	
	}
	count--;

}

void Collisionengine::clean()
{
}
