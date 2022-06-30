#pragma once

class TextureRect2
{
public:
	TextureRect2(Vector3 position, Vector3 size, float rotation, wstring path);
	TextureRect2(Vector3 position, Vector3 size, float rotation = 0.0f); //header에다만 초기화를 시켜주는게 보기좋다.
	virtual ~TextureRect2();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);

	void Update();
	void UpdateWorld();
	void Render();
	virtual void Move();

	void GUI();

	string MakeLabel(string preFix);

	void MapVertexBuffer();
	void UnmapVertexBuffer();

protected:
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world;
	Matrix S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position; 
	Vector3 size;
	float rotation;

	ID3D11ShaderResourceView* srv = nullptr;
};