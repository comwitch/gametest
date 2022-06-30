#include "Framework.h"
#include "TextureRect2.h"

TextureRect2::TextureRect2(Vector3 position, Vector3 size, float rotation, wstring path)
	:position(position), size(size), rotation(rotation)
{
	//vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, -0.0f);
		vertices[0].uv = D3DXVECTOR2(0, 1);

		vertices[1].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = D3DXVECTOR2(1, 0);

		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = D3DXVECTOR2(1, 1);

		vertices[3].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = D3DXVECTOR2(0, 0);
	}

	//VertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	//IndexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_DYNAMIC);
	}

	//VertexShader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	//PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	//InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	//WorldBuffer
	{
		wb = new WorldBuffer();
	}

	//SRV
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
	}
}

TextureRect2::TextureRect2(Vector3 position, Vector3 size, float rotation)
	:position(position), size(size), rotation(rotation)
{
	//vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, -0.0f);
		vertices[0].uv = D3DXVECTOR2(0, 1);

		vertices[1].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = D3DXVECTOR2(1, 0);

		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = D3DXVECTOR2(1, 1);

		vertices[3].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = D3DXVECTOR2(0, 0);
	}

	//VertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	//IndexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	//VertexShader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	//PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	//InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	wb = new WorldBuffer();
}

TextureRect2::~TextureRect2()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(wb);
	SAFE_RELEASE(srv);
}

void TextureRect2::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderPath, "VS");
	ps->Create(shaderPath, "PS");
}

void TextureRect2::Update()
{
	UpdateWorld();
	Move();
}

void TextureRect2::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));

	world = S * R * T;
	wb->SetWorld(world);
}

void TextureRect2::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();
	wb->SetVSBuffer(0);
	DC->PSSetShaderResources(0, 1, &srv);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect2::Move()
{
	/*if (Keyboard::Get()->Press('W'))
		position.y += 100 * Time::Delta();
	else if (Keyboard::Get()->Press('S'))
		position.y -= 100 * Time::Delta();

	if (Keyboard::Get()->Press('D'))
		position.x += 100 * Time::Delta();
	else if (Keyboard::Get()->Press('A'))
		position.x -= 100 * Time::Delta();*/
}

void TextureRect2::GUI()
{
}

string TextureRect2::MakeLabel(string preFix)
{
	return string();
}

void TextureRect2::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TextureRect2::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);

}
