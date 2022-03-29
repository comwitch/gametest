#pragma once

class Rect
{
public:
	Rect(Vector3 position, Vector3 size, float rotation);
	~Rect();

	void Update();
	void Render();
	
	void Move();

	void GUI();

	void UpdateWorld();
	void SetColor(Color color) 
	{ 
		this->color = color;
		UpdateColor();
	}

	BoundingBox* GetBox() { return box; }
	bool AABB(BoundingBox* other) { return box->AABB(other); }

	void UpdateColor();
	string MakeLable(string preFix);

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	D3DXVECTOR3 position;
	D3DXVECTOR3 size;
	float rotation;

	Color color = Color(1, 0, 0, 1);

	WorldBuffer* wb = nullptr;

	bool bOpen = true;

	RectEdge* edge = nullptr;
	BoundingBox* box = nullptr;
};