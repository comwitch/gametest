#pragma once



class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
	TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f); //header���ٸ� �ʱ�ȭ�� �����ִ°� ��������.
	virtual ~TextureRect();

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

	//��ġ�����Լ�
	Vector3* GetPos() { return &position; }
	void SetPos(Vector3 Pos) { this->position = Pos; }

	//�浹��� �����Լ� (�⺻ vertex�� ��ġ�� �����ϴ� �κ�)
	void SetCollisionLT(float x, float y) { this->CollisionEdge_LT = { x,y }; }
	void SetCollisionRB(float x, float y) { this->CollisionEdge_RB = { x,y }; }



protected:

	//���۵� ������� ���ؽ����� �ε��� ���� ���긮�ҽ� ���ؽ� ���̴� �ȼ� ���̴� ��ǲ���̾ƿ������� �Ǿ��ִ�.
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;
	

	//world���� ���� �� ����
	Matrix world;
	Matrix S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position; 
	Vector3 size;
	float rotation;


	//���̴� ���ҽ� ��
	ID3D11ShaderResourceView* srv = nullptr;


	

	//�浹 ���� ������
	RectEdge* edge = nullptr;
	BoundingBox* box = nullptr;


	//edge�� �̹����� �°� �浹�������ִ� ����
	Vector2 CollisionEdge_LT = { 0,0 };
	Vector2 CollisionEdge_RB = { 0,0 };
	
};