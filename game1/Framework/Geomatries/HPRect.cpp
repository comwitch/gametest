#include "Framework.h"
#include "HPRect.h"



HPRect::HPRect(Vector3 position, Vector3 size, bool hp, float rotation)
	:position(position), size(size), rotation(rotation), hp(hp)
{
	//vertices
	{
		vertices.assign(4, VertexColor());

		vertices[0].position = D3DXVECTOR3(-0.5f, -0.1f, -0.0f);
		if (hp == false)
			vertices[0].color = { 0,0,0,1 };
		else
			vertices[0].color = { 1,0,0,1 };

		vertices[1].position = D3DXVECTOR3(0.5f, 0.1f, 0.0f);
		if (hp == false)
			vertices[1].color = { 0,0,0,1 };
		else
			vertices[1].color = { 1,0,0,1 };

		vertices[2].position = D3DXVECTOR3(0.5f, -0.1f, 0.0f);
		if (hp == false)
			vertices[2].color = { 0,0,0,1 };
		else
			vertices[2].color = { 1,0,0,1 };

		vertices[3].position = D3DXVECTOR3(-0.5f, 0.1f, 0.0f);
		if (hp == false)
			vertices[3].color = { 0,0,0,1 };
		else
			vertices[3].color = { 1,0,0,1 };
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
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
	}

	//PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
	}

	//InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	wb = new WorldBuffer();
}

HPRect::~HPRect()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(wb);
	SAFE_RELEASE(srv);
}

void HPRect::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderPath, "VS");
	ps->Create(shaderPath, "PS");
}

void HPRect::Update()
{
	UpdateWorld();
	hp_float = -0.5f + ((float)hp_int)/100;

	if (hp == true)
	{
		MapVertexBuffer();
		{
			
			
			vertices[1].position = D3DXVECTOR3(hp_float, 0.1f, 0.0f);

			vertices[2].position = D3DXVECTOR3(hp_float, -0.1f, 0.0f);
		}
		UnmapVertexBuffer();
	}
	
}

void HPRect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, (position).x, (position).y  , (position).z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));

	world = S * R * T;
	wb->SetWorld(world);
}

void HPRect::Render()
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

void HPRect::Move()
{

}

void HPRect::GUI()
{
}

string HPRect::MakeLabel(string preFix)
{
	return string();
}

void HPRect::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void HPRect::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);

}
