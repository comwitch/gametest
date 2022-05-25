#pragma once

class Camera : public SingletonBase<Camera>
{
public:
	friend class SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();

	void UpdateView();

	void  UnProjection(Vector3* out, Vector3 source, Matrix world);

private:
	Camera();
	~Camera();

	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;
	float CameraSpeed = 100.0f;

};