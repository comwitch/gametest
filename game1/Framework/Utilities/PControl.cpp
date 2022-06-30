#include "Framework.h"
#include "PControl.h"
#include "Systems/GData.h"



PControl::PControl()
{
	
}

PControl::~PControl()
{
}

void PControl::Update()
{
	deltaTime += Time::Delta();
	
}



/*

IDLE 함수

*/


void PControl::Idle()
{
	if (FacingWhere == 0)
	{
		(*animator)->SetCurrentAnimClip(L"IdleL");
	}
	else if (FacingWhere == 1)
	{
		(*animator)->SetCurrentAnimClip(L"IdleR");
	}
	else if (FacingWhere == 2)
	{
		(*animator)->SetCurrentAnimClip(L"IdleU");
	}
	else if (FacingWhere == 3)
	{
		(*animator)->SetCurrentAnimClip(L"IdleD");
	}
}


/*

플레이어블 캐릭터의 함수


*/




void PControl::Right(DWORD key, Vector3 * position, float speed, wstring clipName)
{

	if (Keyboard::Get()->Press(key) && attack == 0)
	{

		FacingLeft = false;
		
		if((*position).x < 1100)
			(*position).x += speed * Time::Delta();
		if (UDCheck == false)
		{
			
			FacingWhere = 1;
			(*animator)->SetCurrentAnimClip(clipName);
		}
			
	}
	else if (Keyboard::Get()->Up(key))
		Idle();
}

void PControl::Left(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key) && attack == 0)
	{
		FacingLeft = true;
		
		if ((*position).x > 100)
			(*position).x -= speed * Time::Delta();
		if (UDCheck == false)
		{
			(*animator)->SetCurrentAnimClip(clipName);
			SetFacingWhere(0);
			FacingWhere = 0;
		}

		
			
	}
	else if (Keyboard::Get()->Up(key))
		Idle();
}

void PControl::Up(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key) && attack == 0)
	{
		UDCheck = true;
		FacingWhere = 2;
		(*position).y += speed * Time::Delta();
		(*animator)->SetCurrentAnimClip(clipName);
	}
	else if (Keyboard::Get()->Up(key))
	{
		Idle();
		UDCheck = false;

	}

}

void PControl::Down(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key) && attack == 0)
	{
	UDCheck = true;
	FacingWhere = 3;
	(*position).y -= speed * Time::Delta();
	(*animator)->SetCurrentAnimClip(clipName);
	}
	else if (Keyboard::Get()->Up(key))
	{
	Idle();
	UDCheck = false;

	}
}


void PControl::Attack(DWORD key)
{
	if (Keyboard::Get()->Press(key))
	{
		attack = true;
		if (FacingWhere == 0)
			(*animator)->SetCurrentAnimClip(L"AttackL");
		else if (FacingWhere == 1)
			(*animator)->SetCurrentAnimClip(L"AttackR");
		else if (FacingWhere == 2)
			(*animator)->SetCurrentAnimClip(L"AttackU");
		else if (FacingWhere == 3)
			(*animator)->SetCurrentAnimClip(L"AttackD");

	}
	else if (Keyboard::Get()->Up(key))
	{
		Idle();
		attack = false;
	}


}

void PControl::Skill(DWORD key, DWORD key2)
{

	if (Keyboard::Get()->Press(key))
	{
		attack = true;
		if (FacingWhere == 0)
		{
			(*animator)->SetCurrentAnimClip(L"IdleL");

		}
		else if (FacingWhere == 1)
		{
			(*animator)->SetCurrentAnimClip(L"IdleR");
		}
		else if (FacingWhere == 2)
		{
			(*animator)->SetCurrentAnimClip(L"IdleU");
		}
		else if (FacingWhere == 3)
		{
			(*animator)->SetCurrentAnimClip(L"IdleD");
		}
	}
	else if (Keyboard::Get()->Up(key))
	{
		Idle();
		attack = false;
	}
}





/*
여기서부터 몬스터의 행동 함수


*/



void PControl::move(Vector3 * position, Vector3 * targetPosition, float speed)
{
	(*position).x += (((*targetPosition).x - (*position).x) / 2) * 1 * Time::Delta();
	(*position).y += (((*targetPosition).y - (*position).y) / 2) * 1 * Time::Delta();

	if (((*targetPosition).x - (*position).x) > 0) 
	{
		(*animator)->SetCurrentAnimClip(L"IdleR");
	}
	else
	{
		(*animator)->SetCurrentAnimClip(L"IdleL");
	}



}




/*

여기서부터 투사체의 행동함수




*/



void PControl::ArrowRight(DWORD key, Vector3 * position, float speed, int _FacingWhere)
{
	


	tmp_Face = _FacingWhere;
	{
		if (tmp_Face == 0)
		{
			(*animator)->SetCurrentAnimClip(L"IdleL");
			(*position).x -= speed * Time::Delta();
		}
		else if (tmp_Face == 1)
		{
			(*position).x += speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(L"IdleR");
		}
		else if (tmp_Face == 2)
		{
			(*position).y += speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(L"IdleU");
		}
		else if (tmp_Face == 3)
		{
			(*position).y-= speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(L"IdleD");
		}

	}
	
}

void PControl::collision(Vector3 * position, float speedx , float speedy)
{
	(*position).y += speedy * Time::Delta();
	(*position).x += speedx * Time::Delta();
}


