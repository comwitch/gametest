#include "stdafx.h"
#include "TextureDemo.h"

#include "Geomatries/TextureRect.h"

void TextureDemo::Init()
{
	tr = new TextureRect(Vector3(640, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f, TexturePath + L"Back.png");
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(tr);
}

void TextureDemo::Update()
{
	tr->Update();
}

void TextureDemo::Render()
{
	tr->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
