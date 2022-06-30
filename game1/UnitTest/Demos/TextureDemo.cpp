#include "stdafx.h"
#include "TextureDemo.h"
#include "Geomatries/TextureRect2.h"

void TextureDemo::Init()
{
	tr = new TextureRect2(Vector3(640, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f, TexturePath + L"background.png");
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(tr);
}

void TextureDemo::Update()
{
	tr->Update();
	if (Keyboard::Get()->Press('S'))
		Valid = false;
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

bool TextureDemo::IsValid()
{
	return Valid;
}

void TextureDemo::SetIsValid(bool _valid)
{
	this->Valid = _valid;
}
