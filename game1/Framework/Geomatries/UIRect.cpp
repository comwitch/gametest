#include "Framework.h"
#include "UIRect.h"

#include "Utilities/UIalphabet.h"

UIRect::UIRect(Vector3 position, Vector3 size)
	:TextureRect2(position, size, 0.0f)
{
	SetShader(ShaderPath + L"VertexTexture.hlsl");
	


	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}

	control = new PControl();
	
}

UIRect::~UIRect()
{
}

void UIRect::Update()
{


	MapVertexBuffer();
	{
		vertices[0].uv.x = alphabet->GetCurrentFrame().x;
		vertices[0].uv.y = alphabet->GetCurrentFrame().y + alphabet->GetTexelFrameSize().y;

		vertices[1].uv.x = alphabet->GetCurrentFrame().x + alphabet->GetTexelFrameSize().x;
		vertices[1].uv.y = alphabet->GetCurrentFrame().y;

		vertices[2].uv.x = alphabet->GetCurrentFrame().x + alphabet->GetTexelFrameSize().x;
		vertices[2].uv.y = alphabet->GetCurrentFrame().y + alphabet->GetTexelFrameSize().y;

		vertices[3].uv.x = alphabet->GetCurrentFrame().x;
		vertices[3].uv.y = alphabet->GetCurrentFrame().y;

	}
	UnmapVertexBuffer();

	

	

	__super::Update();
	
}

void UIRect::Render()
{
	srv = alphabet->GetCurrentSRV();

	

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFFF);
	__super::Render();
	DC->PSSetSamplers(0, 1, &point[0]);
	DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFFF);
}

void UIRect::Move()
{
	

}

