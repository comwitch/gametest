#pragma once



class Camera : public SingletonBase<Camera>
{
public:
	friend class SingletonBase<Camera>;

	void Update();
	void Render();

	void Move(float time);
	void Move2();

	void UpdateView();

	void  UnProjection(Vector3* out, Vector3 source, Matrix world);

private:
	Camera();
	~Camera();

	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;
	float temp_position = 0.0f;
	
	float CameraSpeed = 100.0f;

};