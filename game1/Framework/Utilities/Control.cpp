#include "Framework.h"
#include "Control.h"

Control::Control()
{
}

Control::~Control()
{
}

void Control::Update()
{
	deltaTime += Time::Delta();
	keyDown += Time::Delta();
}

void Control::Idle()
{
	if (FacingLeft == true)
	{
		(*animator)->SetCurrentAnimClip(L"IdleL");
	}
	else
	{
		(*animator)->SetCurrentAnimClip(L"IdleR");
	}
}

void Control::Right(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key))
	{
		FacingLeft = false;

		(*position).x += speed * Time::Delta();
		(*animator)->SetCurrentAnimClip(clipName);
	}
	else if (Keyboard::Get()->Up(key))
		Idle();
}

void Control::Left(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key))
	{
		FacingLeft = true;

		(*position).x -= speed * Time::Delta();
		(*animator)->SetCurrentAnimClip(clipName);
	}
	else if (Keyboard::Get()->Up(key))
		Idle();
}

void Control::Up(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key))
	{
		if (FacingLeft == true)
		{
			(*position).y += speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(clipName);
		}
		else
		{
			(*position).y += speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(clipName);
		}

	}
	else if (Keyboard::Get()->Up(key))
		Idle();
}

void Control::Down(DWORD key, Vector3 * position, float speed, wstring clipName)
{
	if (Keyboard::Get()->Press(key))
	{
		if (FacingLeft == true)
		{
			(*position).y -= speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(clipName);
		}
		else
		{
			(*position).y -= speed * Time::Delta();
			(*animator)->SetCurrentAnimClip(clipName);
		}
	}
	else if (Keyboard::Get()->Up(key))
		Idle();
}

void Control::Jump(DWORD key, Vector3 * position, float speed)
{
	deltaTime += Time::Delta();
	
	if (Keyboard::Get()->Press(key) && !(Keyboard::Get()->Down(key)))
	{
		jump = true;
		keyDown = 0.0f;
		deltaTime = 0.0f;
	}
	else if (jump == true)
	{
		if (FacingLeft == true)
		{
			if ((deltaTime - keyDown) < 1.2f)
				(*animator)->SetCurrentAnimClip(L"JumpL");

			if ((deltaTime - keyDown) < 0.4f)
				(*position).y += speed * Time::Delta();
			else if ((deltaTime - keyDown) < 0.6f)
				(*position).y += 40 * Time::Delta();
			else if ((deltaTime - keyDown) < 0.8f)
				(*position).y -= 40 * Time::Delta();
			else if ((deltaTime - keyDown) < 1.2f)
				(*position).y -= (speed) * Time::Delta();
			else if ((deltaTime - keyDown) > 1.3f)
			{
				Idle();
				jump = false;
			}
		}
		else
		{
			if ((deltaTime - keyDown) < 1.2f)
				(*animator)->SetCurrentAnimClip(L"JumpR");

			if ((deltaTime - keyDown) < 0.4f)
				(*position).y += speed * Time::Delta();
			else if ((deltaTime - keyDown) < 0.6f)
				(*position).y += 40 * Time::Delta();
			else if ((deltaTime - keyDown) < 0.8f)
				(*position).y -= 40 * Time::Delta();
			else if ((deltaTime - keyDown) < 1.2f)
				(*position).y -= (speed) * Time::Delta();
			else if ((deltaTime - keyDown) > 1.3f)
			{
				Idle();
				jump = false;
			}
		}
		
	}
}

void Control::Attack(DWORD key)
{
	if (Keyboard::Get()->Down(key))
	{
		KeyRate += Time::Delta();

		if (FacingLeft == true)
		{
			if (KeyRate < 0.03f)
				(*animator)->SetCurrentAnimClip(L"Attack1L");
			else if (KeyRate < 0.045f)
				(*animator)->SetCurrentAnimClip(L"Attack2L");
			else if (KeyRate < 0.055f)
				(*animator)->SetCurrentAnimClip(L"Attack3L");
			else
				KeyRate = 0.0f;
		}
		else
		{
			if (KeyRate < 0.03f)
				(*animator)->SetCurrentAnimClip(L"Attack1R");
			else if (KeyRate < 0.045f)
				(*animator)->SetCurrentAnimClip(L"Attack2R");
			else if (KeyRate < 0.055f)
				(*animator)->SetCurrentAnimClip(L"Attack3R");
			else
				KeyRate = 0.0f;
		}
	}
}

void Control::Skill(DWORD key, DWORD key2)
{

	if (Keyboard::Get()->Press(key))
	{
		if(FacingLeft == true)
			(*animator)->SetCurrentAnimClip(L"Skill1L");
		else
			(*animator)->SetCurrentAnimClip(L"Skill1R");
	}
	else if (Keyboard::Get()->Press(key))
	{
		if (FacingLeft == true)
			(*animator)->SetCurrentAnimClip(L"Skill2L");
		else
			(*animator)->SetCurrentAnimClip(L"Skill2R");
	}
}
