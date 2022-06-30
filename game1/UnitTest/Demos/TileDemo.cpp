#include "stdafx.h"
#include "TileDemo.h"	

#include "Game/TMap.h"

void TMapDemo::Init()
{
	uint spacing = 40;
	uint width = WinMaxWidth / spacing;
	uint height = WinMaxHeight / spacing;
	tm = new TMap(width, height, spacing);
}

void TMapDemo::Destroy()
{
	SAFE_DELETE(tm);
}

void TMapDemo::Update()
{
	tm->Update();
}

void TMapDemo::Render()
{
	tm->Render();
}

void TMapDemo::PostRender()
{
}

void TMapDemo::GUI()
{
	tm->GUI();
}

bool TMapDemo::IsValid()
{
	return true;
}
