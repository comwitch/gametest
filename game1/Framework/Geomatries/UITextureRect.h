#pragma once

class ShadedBuffer2 : public ShaderBuffer
{
public:
	ShadedBuffer2() : ShaderBuffer(&data, sizeof(Data))
	{
		data.Selection = 0;
	}

	int * GetSelectionPtr() { return &data.Selection; }

	struct Data
	{
		int Selection;
		Vector3 dummy;
	};

private:
	Data data;
};

class UITextureRect
{
public:
	UITextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
	UITextureRect(Vector3 position, Vector3 size, float rotation = 0.0f); //header에다만 초기화를 시켜주는게 보기좋다.
	virtual ~UITextureRect();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);

	void Update();
	void UpdateWorld();
	void Render();


	void changeshaded(int i);


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

	ShadedBuffer2* sb = nullptr;

	WorldBuffer* wb = nullptr;

	Vector3 position; 
	Vector3 size;
	float rotation;

	ID3D11ShaderResourceView* srv = nullptr;
};