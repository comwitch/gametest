#include "stdafx.h"
#include "RTTDemo.h"

#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Utilities/RenderTexture.h"

void RTTDemo::Init()
{
	rtt = new RenderTexture();
	r1 = new Rect(Vector3(200, 200, 0), Vector3(100, 100, 1), 0.0f);
	r2 = new Rect(Vector3(300, 300, 0), Vector3(100, 100, 1), 0.0f);
	r3 = new Rect(Vector3(400, 400, 0), Vector3(100, 100, 1), 0.0f);
	rt1 = new TextureRect(Vector3(500, 500, 0), Vector3(500, 500, 1), 0.0f, TexturePath + L"Meow.bmp");
	rt2 = new TextureRect(Vector3(WinMaxWidth - (WinMaxWidth / 4), WinMaxHeight - (WinMaxHeight / 4), 0), Vector3(WinMaxWidth / 4, WinMaxHeight / 4, 0));
	rt2->SetShader(ShaderPath + L"VertexOutline.hlsl");

}

void RTTDemo::Destroy()
{
	SAFE_DELETE(rtt);
	SAFE_DELETE(r1);
	SAFE_DELETE(r2);
	SAFE_DELETE(r3);
	SAFE_DELETE(rt1);
	SAFE_DELETE(rt2);
}

void RTTDemo::Update()
{
	r1->Update();
	r1->Move();
	r2->Update();
	r3->Update();
	rt1->Update();
	rt2->Update();

}

void RTTDemo::Render()
{
	r1->Render();
	r2->Render();
	r3->Render();
	rt1->Render();
	rt2->SetSRV(rtt->GetSRV());
	rt2->Render();
}

void RTTDemo::PostRender()  //화면안에 화면을 또 그리기 위해서 postrender를 사용한다고 보면된다.
{
	Graphics::Get()->InitViewport();
	rtt->RenderToTexture();
	{
		r1->Render();
		r2->Render();
		r3->Render();
		rt1->Render();
	}
}

void RTTDemo::GUI()
{
}
