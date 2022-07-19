#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/GUIDemo.h"
#include "Demos/RectDemo.h"
#include "Demos/TextureDemo.h"

#include "Demos/ShadedDemo.h"
#include "Demos/RTTDemo.h"
#include "Demos/BlurDemo.h"
#include "Demos/CollisionDemo.h"
#include "Demos/AnimationDemo.h"
#include "Demos/PlayerDemo.h"
#include "Demos/TileDemo.h"
#include "Demos/CollisionDemo.h"
#include "Demos/GameoverDemo.h"
#include "Systems/Sound.h"

/*
2022-07-13

DWs Game

Using tools : 
DirectX11, 
Fmod(Version : 2.02),
win api

image, sound source site

sound : https://soundimage.org/
image : 

If you have question, contact to me : tuna831@gmail.com

Have a nice day!
-Dongwon, Kim
*/

void Program::Init()
{
	States::Create();
	Camera::Create();
	CSound::Init();
	
	vpb = new VPBuffer();
	D3DXMatrixLookAtLH(&view, &Vector3(0, 0, 0), &Vector3(0, 0, 1), &Vector3(0, 1, 0));
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)WinMaxWidth, 0.0f, (float)WinMaxHeight, 0, 1);
	vpb->SetView(view);
	vpb->SetProj(proj);

	
	Push(new TextureDemo());
	Push(new PlayerDemo());

}

void Program::Destroy()
{
	SAFE_DELETE(vpb);
	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
	CSound::Release();
}

void Program::Update()
{
		

	if (objs[count]->IsValid() == true)
		objs[count]->Update();
	else
		count++;

	
	if (count == objs.size())
	{
		count = 0;
		for (IObject* obj : objs)
		{
			obj->SetIsValid(true);
		}

	}
	
	
}

void Program::Render()
{
	vpb->SetVSBuffer(1);
	

	if (objs[count]->IsValid() == true)
		objs[count]->Render();
	
}

void Program::PostRender()
{

	if (objs[count]->IsValid() == true)
		objs[count]->PostRender();

}

void Program::GUI()
{
	

	if (objs[count]->IsValid() == true)
		(*objs[count]).GUI();

}

void Program::Push(IObject * obj)
{
	objs.push_back(obj);
	obj->Init();
}

bool Program::IsValid()
{
	return true;
}



void Program::SetIsValid(bool _valid)
{

}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));


	
	DXDesc desc;
	

	desc.AppName = L"GAME1";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	
	WPARAM wParam = window->Run(program);
	SAFE_DELETE(window);
	SAFE_DELETE(program);
	
	return wParam;

}

