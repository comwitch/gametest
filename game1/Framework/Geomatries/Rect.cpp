#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
	:position(position), size(size), rotation(rotation)
{
	//vertices
	{
		vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertices[0].color = Color(1, 0, 0, 1);

		vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertices[1].color = Color(1, 0, 0, 1);

		vertices[2].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		vertices[2].color = Color(1, 0, 0, 1);

		vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		vertices[3].color = Color(1, 0, 0, 1);
	}

	//vertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	//indexBuffer
	{
		indices = { 0, 1, 2, 2, 1, 3 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	//vertexShader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
	}

	//inputLayout
	{
		il = new InputLayout();
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	//pixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
	}

	//world
	{
		wb = new WorldBuffer();
	}

	edge = new RectEdge();
	box = new BoundingBox(edge);
}

Rect::~Rect()
{

	SAFE_DELETE(edge);
	SAFE_DELETE(box);

	SAFE_DELETE(wb);

	SAFE_DELETE(il);

	SAFE_DELETE(vs);
	SAFE_DELETE(ps);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void Rect::Update()
{
	UpdateWorld();
}

void Rect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::Move()
{
	if (Keyboard::Get()->Press('W'))
		position.y += 100 * Time::Delta();
	else if (Keyboard::Get()->Press('S'))
		position.y -= 100 * Time::Delta();

	if (Keyboard::Get()->Press('A'))
		position.x -= 100 * Time::Delta();
	else if (Keyboard::Get()->Press('D'))
		position.x += 100 * Time::Delta();
}

void Rect::GUI()
{
	ImGui::Begin("Rect", &bOpen);
	{
		ImGui::InputFloat3(MakeLable("Pos").c_str(), position, 2);
		ImGui::InputFloat3(MakeLable("Size").c_str(), size, 2);
		ImGui::SliderAngle(MakeLable("Rot").c_str(), &rotation);
		if (ImGui::ColorPicker4("Color", color))
			UpdateColor();
	}
	ImGui::End();
}

void Rect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);

	world = S * R* T;
	wb->SetWorld(world);

	D3DXVec3TransformCoord(&edge->LT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&edge->RB, &vertices[2].position, &world);
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexColor& v : vertices)
			v.color = color;
		
		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLable(string preFix)
{
	string label = preFix + "##" + to_string((uint)this);
	return label;
}
