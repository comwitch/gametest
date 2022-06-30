#pragma once

#include "Tile.h"
#include "TileSet.h"

enum EDrawingMode
{
	Normal,
	RedCell,
};

enum ColorChoice
{
	Default,
};

class IndexNumBuffer : public ShaderBuffer
{
public:
	IndexNumBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.index = 0;
	}

	void SetIndex(uint index) { data.index = index; }

	struct Data
	{
		uint index;
		Vector3 dummy;
	};

private:
	Data data;
};

class TMap
{
public:
	TMap(uint width, uint height, uint spacing);
	~TMap();

	void Update();
	void Render();
	void GUI();

	void GenerateTileMap();
	void MapVertexBuffer();
	void UnmapVertexBuffer();
	Tile* GetTile(Vector3 mPos);

	void Build();
	void FindPath(Tile* start, Tile* end);

private:
	uint width = 0;
	uint height = 0;
	uint spacing = 0;

	uint vertexCount = 0;
	uint indexCount = 0;

	vector<VertexTile> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world = Values::Identity;
	WorldBuffer* wb = nullptr;

	IndexNumBuffer* inb = nullptr;

	class Tile** tiles = nullptr;

	EDrawingMode mode = Normal;
	ColorChoice choice = Default;
};

//aabb 바운딩 박스 설정