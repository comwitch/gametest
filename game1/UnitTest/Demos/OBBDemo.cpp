#include "stdafx.h"
#include "OBBDemo.h"

#include "Geomatries/OBBRect.h"

void OBBDemo::Init()
{
	ob1 = new OBBRect(Vector3(100, 100, 0), Vector3(100, 100 ,1), 45.0f);
	ob2 = new OBBRect(Vector3(300, 300, 0), Vector3(100, 100, 1), 80.0f);
}

void OBBDemo::Destroy()
{
	SAFE_DELETE(ob1);
	SAFE_DELETE(ob2);
}

void OBBDemo::Update()
{
	ob1->Update();
	ob2->Update();
	if (OBB::CheckIntersect(ob1->GetOBB(), ob2->GetOBB()))
		ob2->SetColor(Values::White);
	else
		ob2->SetColor(Values::Red);

	ob1->Move();
}

void OBBDemo::Render()
{
	ob1->Render();
	ob2->Render();
}

void OBBDemo::PostRender()
{
}

void OBBDemo::GUI()
{
	ob2->GUI();
}
