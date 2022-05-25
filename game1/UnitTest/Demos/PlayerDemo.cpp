#include "stdafx.h"
#include "PlayerDemo.h"
#include "Systems/Camera.h"
#include "Game/Player.h"

void PlayerDemo::Init()
{
	tr = new TextureRect(Vector3(1280, 360, 0), Vector3(WinMaxWidth*2, WinMaxHeight, 1), 0.0f, TexturePath + L"Back.png");
	player = new Player({ 640, 360, 0 }, { 100, 100, 1 });

}

void PlayerDemo::Destroy()
{
	SAFE_DELETE(player);
	SAFE_DELETE(tr);
}

void PlayerDemo::Update()
{
	
	tr->Update();
	player->Update();
	player->Move();
	
}

void PlayerDemo::Render()
{
	
	tr->Render();
	player->Render();
}

void PlayerDemo::PostRender()
{
}

void PlayerDemo::GUI()
{
}
