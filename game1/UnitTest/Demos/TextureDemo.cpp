#include "stdafx.h"
#include "TextureDemo.h"
#include "Geomatries/TextureRect2.h"
#include "Game/UI.h"


void TextureDemo::Init()
{
	tr = new TextureRect2(Vector3(640, 360, 0.1), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f, TexturePath + L"background.png");
	startUI = new UI(Vector3(640, 250, 0), Vector3(400, 100, 1), 0);
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(tr);
	
}

void TextureDemo::Update()
{
	tr->Update();
	startUI->UpdateStart();



	if (startUI->GetPressWhat() == 1)
		Valid = false;
}

void TextureDemo::Render()
{
	tr->Render();
	startUI->RenderStart();
	
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
