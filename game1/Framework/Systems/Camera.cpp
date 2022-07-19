#include "Framework.h"
#include "Camera.h"

void Camera::Update()
{
	 
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move(float time)
{
	if (((int)time % 3) < 1)
	{
		if ((int)(time * 10) % 2 == 1)
		{
			position.x -= CameraSpeed * Time::Delta();
			temp_position -= CameraSpeed * Time::Delta();
		}
			
		if ((int)(time * 10) % 2 == 0)
		{
			position.x += CameraSpeed * Time::Delta();
			temp_position += CameraSpeed * Time::Delta();
		}
	}
	else
	{
		position.x -= temp_position;
		temp_position = 0;
	}
	

	
	UpdateView();
}


void Camera::Move2()
{
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + Values::FwdVec), &Values::UpVec);
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)WinMaxWidth, 0.0f, (float)WinMaxHeight, 0, 1);
	vpb->SetView(view);
}

void Camera::UnProjection(Vector3 * out, Vector3 source, Matrix world)
{
	Vector3 position = source;

	out->x = (position.x *2.0f / WinMaxWidth) - 1.0f;
	out->y = (position.y *2.0f / WinMaxHeight) - 1.0f;
	out->z = position.z;

	Matrix wvp = world * view*proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);
	D3DXVec3TransformCoord(out, out, &wvp);
	
}

Camera::Camera()
{
	vpb = new VPBuffer();
	D3DXMatrixLookAtLH(&view, &Vector3(0, 0, 0), &Vector3(0, 0, 1), &Vector3(0, 1, 0));
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)WinMaxWidth, 0.0f, (float)WinMaxHeight, 0, 1);
	vpb->SetView(view);
	vpb->SetProj(proj);
}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}
