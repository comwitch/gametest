#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	:TextureRect(position, size, 0.0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");

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

	control = new Control();
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
	
	KeyDown += Time::Delta();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFFF);
	__super::Render();
	DC->PSSetSamplers(0, 1, &point[0]);
	DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFFF);
}

void AnimationRect::Move()
{
	
}

// void AnimationRect::Move()
// {
// 	deltaTime += Time::Delta();
// 
// 	if (Keyboard::Get()->Press(VK_UP) && Keyboard::Get()->Press(VK_RIGHT))
// 	{
// 		if (KeyDown >= 1.3f)
// 		{
// 			position.y += 50 * Time::Delta();
// 			position.x += 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"SprintR");
// 		}
// 		else
// 		{
// 			position.y += 50 * Time::Delta();
// 			position.x += 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkR");
// 		}
// 	}
// 	else if (Keyboard::Get()->Press(VK_UP) && Keyboard::Get()->Press(VK_LEFT))
// 	{
// 		position.y += 50 * Time::Delta();
// 		position.x -= 100 * Time::Delta();
// 		animator->SetCurrentAnimClip(L"WalkL");
// 	}
// 	else if (Keyboard::Get()->Press(VK_DOWN) && Keyboard::Get()->Press(VK_LEFT))
// 	{
// 		position.y -= 50 * Time::Delta();
// 		position.x -= 100 * Time::Delta();
// 		animator->SetCurrentAnimClip(L"WalkL");
// 	}
// 	else if (Keyboard::Get()->Press(VK_DOWN) && Keyboard::Get()->Press(VK_RIGHT))
// 	{
// 		position.y -= 50 * Time::Delta();
// 		position.x += 100 * Time::Delta();
// 		animator->SetCurrentAnimClip(L"WalkR");
// 	}
// 	else if (Keyboard::Get()->Press(VK_LEFT))
// 	{
// 		FacingLeft = true;
// 		
// 		if (KeyDown >= 1.3f)
// 		{
// 			position.x -= 200 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"SprintL");
// 		}
// 		else
// 		{
// 			position.x -= 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkL");
// 		}
// 	}
// 	else if (Keyboard::Get()->Up(VK_LEFT))
// 	{
// 		FacingLeft = true;
// 		animator->SetCurrentAnimClip(L"IdleL");
// 		KeyDown = 0.0f;
// 	}
// 	else if (Keyboard::Get()->Press(VK_RIGHT))
// 	{
// 		FacingLeft = false;
// 		
// 		if (KeyDown >= 1.3f)
// 		{
// 			position.x += 200 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"SprintR");
// 		}
// 		else
// 		{
// 			position.x += 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkR");
// 		}
// 	}
// 	else if (Keyboard::Get()->Up(VK_RIGHT))
// 	{
// 		FacingLeft = false;
// 		animator->SetCurrentAnimClip(L"IdleR");
// 		KeyDown = 0.0f;
// 	}
// 
// 	else if (Keyboard::Get()->Press(VK_UP))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			position.y += 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkL");
// 		}
// 		else
// 		{
// 			position.y += 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkR");
// 		}
// 	}
// 	else if (Keyboard::Get()->Up(VK_UP))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			animator->SetCurrentAnimClip(L"IdleL");
// 		}
// 		else
// 		{
// 			animator->SetCurrentAnimClip(L"IdleR");
// 		}
// 	}
// 	else if (Keyboard::Get()->Press(VK_DOWN))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			position.y -= 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkL");
// 		}
// 		else
// 		{
// 			position.y -= 100 * Time::Delta();
// 			animator->SetCurrentAnimClip(L"WalkR");
// 		}
// 	}
// 	else if (Keyboard::Get()->Up(VK_DOWN))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			animator->SetCurrentAnimClip(L"IdleL");
// 		}
// 		else
// 		{
// 			animator->SetCurrentAnimClip(L"IdleR");
// 		}
// 	}
// 
// 	if (Keyboard::Get()->Press(VK_SPACE) && !(Keyboard::Get()->Down(VK_SPACE)))
// 	{
// 		JumpFlags = true;
// 		KeyDown = 0.0f;
// 		deltaTime = 0.0f;
// 	}
// 	else if (JumpFlags == true)
// 	{
// 		if (FacingLeft == true)
// 		{
// 			if ((deltaTime - KeyDown) < 1.2f)
// 				animator->SetCurrentAnimClip(L"JumpL");
// 
// 			if ((deltaTime - KeyDown) < 0.4f)
// 				position.y += 200 * Time::Delta();
// 			else if ((deltaTime - KeyDown) < 0.6f)
// 				position.y += 40 * Time::Delta();
// 			else if ((deltaTime - KeyDown) < 0.8f)
// 				position.y -= 40 * Time::Delta();
// 			else if ((deltaTime - KeyDown) < 1.2f)
// 				position.y -= 220 * Time::Delta();
// 			else if ((deltaTime - KeyDown) > 1.3f)
// 			{
// 				animator->SetCurrentAnimClip(L"IdleL");
// 				this->JumpFlags = false;
// 			}
// 		}
// 		else
// 		{
// 			if ((deltaTime - KeyDown) < 1.2f)
// 				animator->SetCurrentAnimClip(L"JumpR");
// 
// 			if ((deltaTime - KeyDown) < 0.4f)
// 				position.y += 200 * Time::Delta();
// 			else if ((deltaTime - KeyDown) < 0.6f)
// 				position.y += 40 * Time::Delta();
// 			else if ((deltaTime - KeyDown) < 0.8f)
// 				position.y -= 40 * Time::Delta();
// 			else if ((deltaTime - KeyDown) < 1.2f)
// 				position.y -= 220 * Time::Delta();
// 			else if ((deltaTime - KeyDown) > 1.3f)
// 			{
// 				animator->SetCurrentAnimClip(L"IdleR");
// 				this->JumpFlags = false;
// 			}
// 		}
// 	}
// 
// 	if (Keyboard::Get()->Press('Z'))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			animator->SetCurrentAnimClip(L"Attack1L");
// 		}
// 		else
// 		{
// 			animator->SetCurrentAnimClip(L"Attack1R");
// 		}
// 	}
// 
// 	if (Keyboard::Get()->Press('A'))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			animator->SetCurrentAnimClip(L"Skill1L");
// 		}
// 		else
// 		{
// 			animator->SetCurrentAnimClip(L"Skill1R");
// 		}
// 	}
// 
// 	if (Keyboard::Get()->Press('S'))
// 	{
// 		if (FacingLeft == true)
// 		{
// 			animator->SetCurrentAnimClip(L"Skill2L");
// 		}
// 		else
// 		{
// 			animator->SetCurrentAnimClip(L"Skill2R");
// 		}
// 	}
//}
