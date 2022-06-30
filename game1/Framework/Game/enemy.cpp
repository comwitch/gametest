#include "Framework.h"
#include "enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"enemy1.png"); // 이미지 소스

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	
	// idle Anim
	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 8, Vector2(0, 0), Vector2(texSize.x * 0.8f, texSize.y), 1.0f / 15);
	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 8, Vector2(texSize.x * 0.8f, 0), Vector2(0, texSize.y), 1.0f / 15, true);


	// enemy checker
	animRect->SetCharacter(1); 

	animator->SetAnim(IdleR);
	animator->SetAnim(IdleL);

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

}

void Enemy::Render()
{
	animRect->Render();
}
