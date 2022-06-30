#pragma once

class HPRect
{
public:
	HPRect(Vector3 position, Vector3 size,  bool hp, float rotation = 0.0f); //header에다만 초기화를 시켜주는게 보기좋다.

	virtual ~HPRect();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);

	void Update();
	void UpdateWorld();
	void Render();
	virtual void Move();

	void GUI();

	void Sethpint(int _hp) { this->hp_int = _hp; }

	string MakeLabel(string preFix);

	void SetPosition(Vector3 _position) { this->position = _position; }
	void MapVertexBuffer();
	void UnmapVertexBuffer();

protected:
	vector<VertexColor> vertices;
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
	Vector3 * position2;

	Vector3 size;
	float rotation;
	bool hp = false;//hp바로 쓸것인지 바탕으로 쓸것인지

	int hp_int = 100;
	float hp_float;

	ID3D11ShaderResourceView* srv = nullptr;
};