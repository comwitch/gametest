#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	:TextureRect(position, size, 0.0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");
	sb = new ShadedBuffer();


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

AnimationRect::~AnimationRect()
{
}

void AnimationRect::Update()
{
	control->SetAnimator(&animator);

	MapVertexBuffer();
	{
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;

	}
	UnmapVertexBuffer();

	

	

	__super::Update();
	
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	sb->SetPSBuffer(0);
	

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFFF);
	__super::Render();
	DC->PSSetSamplers(0, 1, &point[0]);
	DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFFF);
}

void AnimationRect::Move()
{
	
	
	if (Character == 0)
	{
		control->Right(VK_RIGHT, &position, 200, L"WalkR");
		control->Left(VK_LEFT, &position, 200, L"WalkL");
		control->Up(VK_UP, &position, 200, L"WalkU");
		control->Down(VK_DOWN, &position, 200, L"WalkD");
		control->Attack('A');
		control->Skill('S', 'D');
		
	}
	if (Character == 1)
	{
		control->move(&position, &targetpostiont, 100);
	}
	
	if (Character == 2)
	{
		control->ArrowRight('S', &position, 1200, _FacingWhere);
	}

}

bool AnimationRect::AABB(BoundingBox * other)
{
	if (box->AABB(other) == true)
	{
		isCollid = true;
		return true;
	}
	else
	{
		
		return false;
	}
	
}
