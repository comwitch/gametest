#include "stdafx.h"
#include "GameoverDemo.h"
#include "Geomatries/TextureRect2.h"

void GameoverDemo::Init()
{
	tr = new TextureRect2(Vector3(640, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f, TexturePath + L"gameover.png");
}

void GameoverDemo::Destroy()
{
	SAFE_DELETE(tr);
}

void GameoverDemo::Update()
{
	
	if (Keyboard::Get()->Press('F'))
		Valid = false;
	tr->Update();
}

void GameoverDemo::Render()
{
	tr->Render();
}

void GameoverDemo::PostRender()
{
}

void GameoverDemo::GUI()
{
}

bool GameoverDemo::IsValid()
{
	return Valid;
}

void GameoverDemo::SetIsValid(bool _valid)
{
	this->Valid = _valid;
}
