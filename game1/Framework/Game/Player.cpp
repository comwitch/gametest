#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"Stand.png"); // 이미지 소스
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	
	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 9, Vector2(0, 0), Vector2(texSize.x * 0.9f, texSize.y * 0.1f), 1.0f / 10.0f);
	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 9, Vector2(0, texSize.y * 0.1f), Vector2(texSize.x * 0.9f, texSize.y * 0.2f), 1.0f / 10.0f);

	AnimationClip* WalkR = new AnimationClip(L"WalkR", srcTex, 10, Vector2(0, texSize.y * 0.4f), Vector2(texSize.x, texSize.y * 0.5f), 1.0f / 10.0f);
	AnimationClip* WalkL = new AnimationClip(L"WalkL", srcTex, 10, Vector2(0, texSize.y * 0.5f), Vector2(texSize.x, texSize.y * 0.6f), 1.0f / 10.0f);

	AnimationClip* JumpR = new AnimationClip(L"JumpR", srcTex, 6, Vector2(0, texSize.y * 0.6f), Vector2(texSize.x*0.6f, texSize.y * 0.7f), 2.0f / 10.0f);
	AnimationClip* JumpL = new AnimationClip(L"JumpL", srcTex, 6, Vector2(0, texSize.y * 0.7f), Vector2(texSize.x*0.6f, texSize.y * 0.8f), 2.0f / 10.0f, true);

	AnimationClip* SprintR = new AnimationClip(L"SprintR", srcTex, 8, Vector2(0, texSize.y * 0.8f), Vector2(texSize.x*0.8f, texSize.y * 0.9f), 1.0f / 10.0f);
	AnimationClip* SprintL = new AnimationClip(L"SprintL", srcTex, 8, Vector2(0, texSize.y * 0.9f), Vector2(texSize.x*0.8f, texSize.y ), 1.0f / 10.0f);

	
	animator->SetAnim(IdleR);
	animator->SetAnim(IdleL);
	animator->SetAnim(WalkR);
	animator->SetAnim(WalkL);
	animator->SetAnim(JumpR);
	animator->SetAnim(JumpL);
	animator->SetAnim(SprintR);
	animator->SetAnim(SprintL);

	animator->SetCurrentAnimClip(L"IdleR");
	
	animRect->SetAnimation(animator);

	SAFE_DELETE(srcTex);
}

Player::~Player()
{
}

void Player::Update()
{
	animRect->Move();
	animator->Update();
	animRect->Update();
}

void Player::Render()
{
	animRect->Render();
}
