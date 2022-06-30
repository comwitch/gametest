#pragma once

struct VertexColor
{
	VertexColor() : position(0, 0, 0), color(0, 0, 0, 0) {}
	VertexColor(Vector3 position, Color color)
		: position(position), color(color)
	{

	}
	Vector3 position;
	Color color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;
};

struct VertexTexture
{
	VertexTexture() : position(0, 0, 0), uv(0, 0) {}
	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv)
	{

	}
	Vector3 position;
	Vector2 uv;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;
};

struct VertexTextureColor
{
	VertexTextureColor() : position(0, 0, 0), uv(0, 0), color(0, 0, 0, 0) {}
	VertexTextureColor(Vector3 position, Vector2 uv, Color color)
		: position(position), uv(uv), color(color)
	{

	}
	Vector3 position;
	Vector2 uv;
	Color color;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 3;
};

struct VertexTile
{
	VertexTile() : position(0, 0, 0), uv(0, 0), color(0, 0, 0, 0) {}
	VertexTile(Vector3 position, Vector2 uv, Vector2 uv2, Color color, uint index, bool bWalkalbe = true)
		: position(position), uv(uv), uv2(uv2), color(color), index(index), bWalkable(bWalkable)
	{

	}
	Vector3 position;
	Vector2 uv;
	Vector2 uv2;
	Color color;
	uint index;
	bool bWalkable;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 6;
};
