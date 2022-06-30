#pragma once



class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
	TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f); //header에다만 초기화를 시켜주는게 보기좋다.
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

	//위치관련함수
	Vector3* GetPos() { return &position; }
	void SetPos(Vector3 Pos) { this->position = Pos; }

	//충돌경계 설정함수 (기본 vertex에 수치를 조정하는 부분)
	void SetCollisionLT(float x, float y) { this->CollisionEdge_LT = { x,y }; }
	void SetCollisionRB(float x, float y) { this->CollisionEdge_RB = { x,y }; }



protected:

	//버퍼들 순서대로 버텍스버버 인덱스 버퍼 서브리소스 버텍스 셰이더 픽셀 계이더 인풋레이아웃순으로 되어있다.
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;
	

	//world관련 변수 및 버퍼
	Matrix world;
	Matrix S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position; 
	Vector3 size;
	float rotation;


	//셰이더 리소스 뷰
	ID3D11ShaderResourceView* srv = nullptr;


	

	//충돌 구현 변수들
	RectEdge* edge = nullptr;
	BoundingBox* box = nullptr;


	//edge를 이미지에 맞게 충돌설정해주는 변수
	Vector2 CollisionEdge_LT = { 0,0 };
	Vector2 CollisionEdge_RB = { 0,0 };
	
};