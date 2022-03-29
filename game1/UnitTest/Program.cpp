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

void Program::Init()
{
	States::Create();

	vpb = new VPBuffer();
	D3DXMatrixLookAtLH(&view, &Vector3(0, 0, 0), &Vector3(0, 0, 1), &Vector3(0, 1, 0));
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)WinMaxWidth, 0.0f, (float)WinMaxHeight, 0, 1);
	vpb->SetView(view);
	vpb->SetProj(proj);

	//Push(new RectDemo());
	Push(new TextureDemo());
	//Push(new GUIDemo);
	//Push(new ShadedDemo());
	//Push(new RTTDemo());
	//Push(new BlurDemo());
	//Push(new CollisionDemo());
	//Push(new AnimationDemo());
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
}

void Program::Update()
{
	for (IObject* obj : objs)
	{
		obj->Update();
	}
}

void Program::Render()
{
	vpb->SetVSBuffer(1);
	for (IObject* obj : objs)
	{
		obj->Render();
	}
}

void Program::PostRender()
{
	for (IObject* obj : objs)
	{
		obj->PostRender();
	}
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject * obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
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
