#pragma once

struct RectEdge
{
	Vector3 LT;
	Vector3 RB;
};

class BoundingBox
{
public:
	BoundingBox(RectEdge* edge);
	~BoundingBox();

	bool AABB(BoundingBox* ohter);

private:
	RectEdge* edge = nullptr;
};