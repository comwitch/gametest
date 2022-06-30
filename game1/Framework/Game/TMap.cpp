#include "Framework.h"
#include "TMap.h"
#include "TileSet.h"
#include "Tile.h"

TMap::TMap(uint width, uint height, uint spacing)
	: width(width), height(height), spacing(spacing)
{
	TileSet::Create();

	GenerateTileMap();
	//tiles[height / 2][width / 2].SetColor(Values::Red);

	vertices.assign(4, VertexTile());
	vertices[0].position = Values::ZeroVec3;
	vertices[1].position = Vector3(0.0f, (float)spacing, 0.0f);
	vertices[2].position = Vector3((float)spacing, 0.0f, 0.0f);
	vertices[3].position = Vector3((float)spacing, (float)spacing, 0.0f);

	indices = { 0,1,2,2,1,3 };

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"VertexTile.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"VertexTile.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

	wb = new WorldBuffer();
	wb->SetWorld(world);

	inb = new IndexNumBuffer();
	inb->SetIndex(0);


	PathFinder::Create();
}

TMap::~TMap()
{
	TileSet::Delete();

	for (uint y = 0; y < height; y++)
		SAFE_DELETE_ARRAY(tiles[y]);
	SAFE_DELETE_ARRAY(tiles);

	SAFE_DELETE(wb);
	SAFE_DELETE(inb);

	SAFE_DELETE(il);

	SAFE_DELETE(vs);
	SAFE_DELETE(ps);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void TMap::Update()
{
	Vector3 mPos = Mouse::Get()->GetPosition();
	Tile* tile = GetTile(mPos);
	if (tile != nullptr)
	{
		inb->SetIndex(tile->GetIndex());
	}

	if (Mouse::Get()->Press(0))
	{
		if (tile != nullptr)
		{
			tile->SetColor(Values::Red);
			Vector2 startUV = TileSet::Get()->selectedStartUV;
			Vector2 endUV = startUV + TileSet::Get()->texelTileSize;
			tile->SetStartUV(TileSet::Get()->selectedStartUV);
			tile->SetEndUV(endUV);
			if (mode == RedCell)
			{
				tile->SetIsWalkable(false);
			}
		}
	}

	if (Keyboard::Get()->Down(VK_SPACE))
	{
		Build();
		FindPath(nullptr, nullptr);
	}
}

void TMap::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();

	//l-value, r-value
	DC->PSSetShaderResources(0, 1, &TileSet::Get()->tileSRV);
	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];

			MapVertexBuffer();
			{
				for (VertexTile& v : vertices)
				{
					v.color = tile.GetColor();
					v.bWalkable = tile.GetIsWalkable();
					v.index = tile.GetIndex();
				}

				vertices[0].uv = Vector2(tile.GetStartUV().x, tile.GetEndUV().y);
				vertices[1].uv = tile.GetStartUV();
				vertices[2].uv = tile.GetEndUV();
				vertices[3].uv = Vector2(tile.GetEndUV().x, tile.GetStartUV().y);

				vertices[0].uv2 = Vector2(0, 1);
				vertices[1].uv2 = Vector2(0, 0);
				vertices[2].uv2 = Vector2(1, 1);
				vertices[3].uv2 = Vector2(1, 0);
			}
			UnmapVertexBuffer();

			world = DXMath::Translation(tile.GetPosition());
			wb->SetWorld(world);
			wb->SetVSBuffer(0);
			inb->SetPSBuffer(0);
			DC->DrawIndexed(ib->GetCount(), 0, 0);
		}
	}
}

void TMap::GUI()
{
	TileSet::Get()->GUI();


	ImGui::Begin("TileMap");
	{
		ImGui::RadioButton("Normal", (int*)&mode, 0);
		ImGui::RadioButton("RedCell", (int*)&mode, 1);
	}
	ImGui::End();
}

void TMap::GenerateTileMap()
{
	if (width == 0 || height == 0 || spacing == 0)
		assert(false);

	tiles = new Tile*[height];
	int index = 0;
	for (uint y = 0; y < height; y++)
	{
		tiles[y] = new Tile[width];
		for (uint x = 0; x < width; x++)
		{
			tiles[y][x].SetPosition(Vector3((float)(x * spacing), (float)(y * spacing), 0.0f));
			tiles[y][x].SetIndex(index++);
		}
	}
}

void TMap::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TMap::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

Tile * TMap::GetTile(Vector3 mPos)
{
	uint x = (int)mPos.x / spacing;
	uint y = (int)mPos.y / spacing;

	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr;

	return &tiles[y][x];
}

void TMap::Build()
{
	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			tiles[y][x].Release();
		}
	}

	int newX = 0, newY = 0;

	Tile* child = nullptr;
	Tile* current = nullptr;

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			current = &tiles[y][x];
			for (int i = -1; i < 2; i++)
			{
				newY = y + i;
				for (int j = -1; j < 2; j++)
				{
					newX = x + j;
					if (newY > -1 && newY < (int)height
						&& newX > -1 && newX < (int)width)
					{
						child = &tiles[newY][newX];
						if (child->GetIsWalkable() == true
							&& current != child
							&& (newX == x || newY == y))
						{
							tiles[y][x].AddChild(make_pair(child, (float)spacing));
						}
					}
				}
			}
		}
	}
}

void TMap::FindPath(Tile * start, Tile * end)
{
	vector<Tile*>path;
	bool result = PathFinder::Get()->GetPath(&tiles[0][0], &tiles[height - 1][width - 1], path);

	if (result == true)
	{
		for (Tile* node : path)
		{
			node->SetColor(Values::Green);
		}
	}
}