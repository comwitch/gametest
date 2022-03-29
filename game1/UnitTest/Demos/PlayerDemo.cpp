#include "stdafx.h"
#include "PlayerDemo.h"

#include "Game/Player.h"

void PlayerDemo::Init()
{
	player = new Player({ 640, 360, 0 }, { 600, 400, 1 });
}

void PlayerDemo::Destroy()
{
	SAFE_DELETE(player);
}

void PlayerDemo::Update()
{
	player->Update();
}

void PlayerDemo::Render()
{
	player->Render();
}

void PlayerDemo::PostRender()
{
}

void PlayerDemo::GUI()
{
}
