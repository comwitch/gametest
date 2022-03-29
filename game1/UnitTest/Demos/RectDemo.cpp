#include "stdafx.h"
#include "RectDemo.h"

#include "Geomatries/Rect.h"

void RectDemo::Init()
{
}

void RectDemo::Destroy()
{
	for (Rect* r : rects)
		SAFE_DELETE(r);
}

void RectDemo::Update()
{
	if (Mouse::Get()->Down(0))
		rects.push_back(new Rect(Mouse::Get()->GetPosition(), Vector3(100, 100, 1), 0.0f));
	for (Rect* r : rects)
		r->Update();
}

void RectDemo::Render()
{
	for (Rect* r : rects)
		r->Render();
}

void RectDemo::PostRender()
{
}

void RectDemo::GUI()
{
	/*ImGui::Begin("Rects");
	{
		for (Rect* r : rects)
			r->GUI();
	}
	ImGui::End();*/
}
