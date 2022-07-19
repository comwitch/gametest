#pragma once
#include "TextureRect.h"


class ShadedBuffer23 : public ShaderBuffer
{
public:
	ShadedBuffer23() : ShaderBuffer(&data, sizeof(Data))
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

class ShadedTexture : public TextureRect
{
public:
	ShadedTexture(Vector3 position, Vector3 size, float rotation);
	~ShadedTexture();

	void Render();
	void GUI();

	ShadedBuffer23* GetSB() { return sb; }

private:
	ShadedBuffer23* sb = nullptr;
};