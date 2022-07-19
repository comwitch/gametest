#include "Framework.h"
#include "enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"enemy1.png"); // 이미지 소스
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"enemy2.png"); // 이미지 소스
	Texture2D* srcTex3 = new Texture2D(TexturePath + L"enemy6.png"); // 이미지 소스
	Texture2D* srcTex4 = new Texture2D(TexturePath + L"enemy5.png"); // 이미지 소스
	Texture2D* srcTex5 = new Texture2D(TexturePath + L"die.png"); // 이미지 소스

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	


	// idle Anim
	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 8, Vector2(0, 0), Vector2(texSize.x * 0.8f, texSize.y), 1.0f / 15);
	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 8, Vector2(texSize.x * 0.8f, 0), Vector2(0, texSize.y), 1.0f / 15, true);
	AnimationClip* IdleR2 = new AnimationClip(L"IdleR2", srcTex2, 9, Vector2(0, 0), Vector2(texSize.x * 0.9f, texSize.y), 1.0f / 15);
	AnimationClip* IdleL2 = new AnimationClip(L"IdleL2", srcTex2, 9, Vector2(0, 0), Vector2(texSize.x * 0.9f, texSize.y), 1.0f / 15, true);
	AnimationClip* IdleR3 = new AnimationClip(L"IdleR3", srcTex3, 6, Vector2(0, 0), Vector2(texSize.x * 0.6f, texSize.y), 1.0f / 15);
	AnimationClip* IdleL3 = new AnimationClip(L"IdleL3", srcTex3, 6, Vector2(0, 0), Vector2(texSize.x * 0.6f, texSize.y), 1.0f / 15, true);
	AnimationClip* IdleR4 = new AnimationClip(L"IdleR4", srcTex4, 6, Vector2(0, 0), Vector2(texSize.x * 0.6f, texSize.y), 1.0f / 15);
	AnimationClip* IdleL4 = new AnimationClip(L"IdleL4", srcTex4, 6, Vector2(0, 0), Vector2(texSize.x * 0.6f, texSize.y), 1.0f / 15, true);
	AnimationClip* die = new AnimationClip(L"die", srcTex5, 5, Vector2(0, 0), Vector2(texSize.x * 0.5f, texSize.y), 1.0f / 15);

	// enemy checker
	animRect->SetCharacter(1); 

	animator->SetAnim(IdleR);
	animator->SetAnim(IdleL);
	animator->SetAnim(IdleR2);
	animator->SetAnim(IdleL2);
	animator->SetAnim(IdleR3);
	animator->SetAnim(IdleL3);
	animator->SetAnim(IdleR4);
	animator->SetAnim(IdleL4);
	animator->SetAnim(die);

	animator->SetCurrentAnimClip(L"IdleR");

	
	animRect->SetAnimation(animator);



	//콜리젼 경계
	SetCollision(28, 22, 20, 28);


	SAFE_DELETE(srcTex);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	
	animator->Update();
	animRect->Update();
	if (animRect->GetHp() <= 0)
	{
		animator->SetCurrentAnimClip(L"die");
		dietime += Time::Delta();
	}


}

void Enemy::Render()
{
	animRect->Render();
}
