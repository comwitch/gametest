#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"jelda.png"); // 이미지 소스
	

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	AnimationClip* WalkU = new AnimationClip(L"WalkD", srcTex, 10, Vector2(0, 0), Vector2(texSize.x, texSize.y * 0.25f), 1.0f / 20.0f);
	AnimationClip* WalkD = new AnimationClip(L"WalkL", srcTex, 10, Vector2(0, texSize.y * 0.25f), Vector2(texSize.x , texSize.y * 0.5f), 1.0f / 20.0f);
	AnimationClip* WalkR = new AnimationClip(L"WalkU", srcTex, 10, Vector2(0, texSize.y * 0.5f), Vector2(texSize.x, texSize.y * 0.75f), 1.0f / 20.0f);
	AnimationClip* WalkL = new AnimationClip(L"WalkR", srcTex, 10, Vector2(0, texSize.y * 0.75f), Vector2(texSize.x, texSize.y ), 1.0f / 20.0f);





	animator->SetAnim(WalkU);
	animator->SetAnim(WalkD);
	animator->SetAnim(WalkR);
	animator->SetAnim(WalkL);



	animator->SetCurrentAnimClip(L"WalkD");

	animRect->SetAnimation(animator);

	SAFE_DELETE(srcTex);

	control = new Control();
}

Player::~Player()
{
	SAFE_DELETE(control);
}

void Player::Update()
{
	
	control->SetAnimator(animRect->GetAnimator());
	animRect->Move();
	animator->Update();
	animRect->Update();
}




void Player::Render()
{
	animRect->Render();
}

void Player::Move()
{
	

	control->Right(VK_RIGHT, animRect->GetPosition(), 200, L"WalkR");
	control->Left(VK_LEFT, animRect->GetPosition(), 200, L"WalkL");
	control->Up(VK_UP, animRect->GetPosition(), 200, L"WalkU");
	control->Down(VK_DOWN, animRect->GetPosition(), 200, L"WalkD");

}
