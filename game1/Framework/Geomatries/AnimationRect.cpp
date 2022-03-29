#include "Framework.h"
#include "AnimationRect.h"
#include "Systems/Time.h"
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
}

AnimationRect::~AnimationRect()
{
}

void AnimationRect::Update()
{
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

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFFF);
	__super::Render();
	DC->PSSetSamplers(0, 1, &point[0]);
	DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFFF);
}

void AnimationRect::Move()
{
	deltatime2 += Time::Delta();
	
	

	if (Keyboard::Get()->Press(VK_UP) && Keyboard::Get()->Press(VK_RIGHT))
	{
		position.y += 50 * Time::Delta();
		position.x += 100 * Time::Delta();
		animator->SetCurrentAnimClip(L"WalkR");
	}
	else if (Keyboard::Get()->Press(VK_UP) && Keyboard::Get()->Press(VK_LEFT))
	{
		position.y += 50 * Time::Delta();
		position.x -= 100 * Time::Delta();
		animator->SetCurrentAnimClip(L"WalkL");
	}
	else if (Keyboard::Get()->Press(VK_DOWN) && Keyboard::Get()->Press(VK_LEFT))
	{
		position.y -= 50 * Time::Delta();
		position.x -= 100 * Time::Delta();
		animator->SetCurrentAnimClip(L"WalkL");
	}
	else if (Keyboard::Get()->Press(VK_DOWN) && Keyboard::Get()->Press(VK_RIGHT))
	{
		position.y -= 50 * Time::Delta();
		position.x += 100 * Time::Delta();
		animator->SetCurrentAnimClip(L"WalkR");
	}
	else if (Keyboard::Get()->Press(VK_LEFT))
	{
		if (Keyboard::Get()->Press('Z'))
		{
			KeyDown = Time::Delta();
			cout << KeyDown << endl;
			position.x -= 128 * Time::Delta();
			KeyDown2 += KeyDown;
			if (KeyDown2 > 0.5f)
			{
				position.x -= 200 * Time::Delta();
				animator->SetCurrentAnimClip(L"SprintL");
			}

		}
		
		else
		{
			KeyDown2 = 0;
			position.x -= 200 * Time::Delta();
			animator->SetCurrentAnimClip(L"WalkL");
		}
		
	}
	else if (Keyboard::Get()->Press(VK_RIGHT))
	{
		
		if (Keyboard::Get()->Press('Z'))
		{
			KeyDown = Time::Delta();
			cout << KeyDown << endl;
			position.x += 128 * Time::Delta();
				KeyDown2 += KeyDown;
				if (KeyDown2 > 0.5f)
				{
					position.x += 128 * Time::Delta();
					animator->SetCurrentAnimClip(L"SprintR");
				}
							
		}
		
		else
		{
			position.x += 128 * Time::Delta();
			animator->SetCurrentAnimClip(L"WalkR");
			KeyDown2 = 0;
		}

		
	}
	
	else if (Keyboard::Get()->Up(VK_RIGHT))
	{
		animator->SetCurrentAnimClip(L"IdleR");
	}
	else if (Keyboard::Get()->Up(VK_LEFT))
	{
		animator->SetCurrentAnimClip(L"IdleL");
	}

	

	if (Keyboard::Get()->Press(VK_UP))
	{

		position.y += 100 * Time::Delta();

	}
	else if (Keyboard::Get()->Press(VK_DOWN))
	{
		position.y -= 100 * Time::Delta();

	}
	else if (Keyboard::Get()->Press(VK_SPACE) && !(Keyboard::Get()->Down(VK_SPACE)))
	{
		JumpFlag = 1;
		KeyDown2 = 0;
		deltatime2 = 0;
	}
	else if (JumpFlag == 1)
	{
		
		if ((deltatime2 - KeyDown2) < 1.2f)
			animator->SetCurrentAnimClip(L"JumpL");

		if ((deltatime2 - KeyDown2) < 0.4f)
			position.y += 200 * Time::Delta();
		else if ((deltatime2 - KeyDown2) < 0.6f)
			position.y += 40 * Time::Delta();
		else if ((deltatime2 - KeyDown2) < 0.8f)
			position.y -= 40 * Time::Delta();
		else if ((deltatime2 - KeyDown2) < 1.2f)
			position.y -= 220 * Time::Delta();
		else if ((deltatime2 - KeyDown2) > 1.3f)
		{
			animator->SetCurrentAnimClip(L"idleR");
			this->JumpFlag = 0;

		}

	}
	/*else if (JumpFlag == 1)
	{
		if (deltatime2 < 1.2f)
			animator->SetCurrentAnimClip(L"JumpR");

		if ((deltatime2 - KeyDown2) < 0.4f)
			position.y += 200 * Time::Delta();
		else if ((deltatime2 - KeyDown2) < 0.6f)
			position.y += 40 * Time::Delta();
		else if ((deltatime2 - KeyDown2) < 0.8f)
			position.y -= 40 * Time::Delta();
		else if ((deltatime2 - KeyDown2) < 1.2f)
			position.y -= 200 * Time::Delta();
	}*/
	

	
	
	else if (Keyboard::Get()->Up('Z'))
	{
	
	}
	

	if (Keyboard::Get()->Press('A'))
	{
	
	}
	if (Keyboard::Get()->Press('S'))
	{
	
	}

}
