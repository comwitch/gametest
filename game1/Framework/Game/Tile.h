#pragma once

class Tile
{
	friend class PathFinder;
public:
	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 position) { this->position = position; }

	Vector2 GetStartUV() { return startUV; }
	void SetStartUV(Vector2 startUV) { this->startUV = startUV; }

	Vector2 GetEndUV() { return endUV; }	
	void SetEndUV(Vector2 endUV) { this->endUV = endUV; }

	Color GetColor() { return color; }
	void SetColor(Color color) { this->color = color; }

	float GetDistance(Tile* node);
	void AddChild(pair<Tile*, float> child)
	{
		childs.push_back(child);

	}

	void Release()
	{
		isOpen = isClose = false;
		f = g = h = 0.0f;
		childs.clear();
		parentNode = nullptr;
		color = isWalkable ? Values::Black : Values::Red;
	}

	float GetF() { return f; }

	bool GetIsWalkable() { return isWalkable; }
	void SetIsWalkable(bool isWalkable) { this->isWalkable = isWalkable; }

	uint GetIndex() { return index; }
	void SetIndex(uint index) { this->index = index; }

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

	string GetSpriteName() { return spritename; }
	void SetSpriteName(string spriteName) { this->spritename = spritename; }



private:
	Vector3 position = Values::ZeroVec3;
	Color color = Values::Black;
	Vector2 startUV = Values::ZeroVec2;
	Vector2 endUV = Values::ZeroVec2;

	ID3D11ShaderResourceView* srv = nullptr;

	bool isWalkable = true;

	string spritename = "";

	uint index = -1;

	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	bool isOpen = false;
	bool isClose = false;

	Tile* parentNode = nullptr;
	vector<pair<Tile*, float>> childs;
};

class PathFinder : public SingletonBase<PathFinder>
{
public:
	friend class SingletonBase<PathFinder>;
	typedef pair<Tile*, float> ChildNode;

public:
	bool GetPath(Tile* start, Tile* end, vector<Tile*>& path);
	static void ReConstructPath(Tile* node, vector<Tile*>& path);

	void Clear();

private:
	PathFinder() = default;
	~PathFinder() = default;

	vector<Tile*> openList;
	vector<Tile*> closeList;
};