#include "Framework.h"
#include "Player.h"
#include "Game/Arrow.h"
#include "Geomatries/HPRect.h"




Player::Player(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"chmov.png"); // 이미지 소스
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"chmov.png");
	Texture2D* srcTex3 = new Texture2D(TexturePath + L"sidewalk.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	Vector2 texSize2 = Vector2(srcTex2->GetWidth(), srcTex2->GetHeight());
	Vector2 texSize3 = Vector2(srcTex3->GetWidth(), srcTex3->GetHeight());


	HP1 = new HPRect(position, { 50, 50, 1 },false, 0);
	HP2 = new HPRect(position, { 50, 50, 1 },true, 0);
	
	

	
	// idle Anim
	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 1, Vector2(0, texSize.y*0.1), Vector2(texSize.x * 0.1f, texSize2.y*0.2f), 1.0f / 15);
	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 1, Vector2(0, 0), Vector2(texSize.x * 0.1f, texSize.y * 0.1f), 1.0f / 10.0f);
	AnimationClip* IdleU = new AnimationClip(L"IdleU", srcTex, 1, Vector2(0, texSize.y*0.2), Vector2(texSize.x * 0.1f, texSize.y * 0.3f), 1.0f / 10.0f);
	AnimationClip* IdleD = new AnimationClip(L"IdleD", srcTex, 1, Vector2(0, texSize.y*0.3), Vector2(texSize.x * 0.1f, texSize.y * 0.4f), 1.0f / 10.0f);


	// Walk Anim
	AnimationClip* WalkL = new AnimationClip(L"WalkL", srcTex, 8, Vector2(0, 0), Vector2(texSize.x * 0.8f, texSize.y * 0.1f ), 1.0f / 10.0f);
	AnimationClip* WalkR = new AnimationClip(L"WalkR", srcTex, 8, Vector2(0, texSize.y * 0.1f), Vector2(texSize.x * 0.8f, texSize.y * 0.2f ), 1.0f / 10.0f);
	AnimationClip* WalkU = new AnimationClip(L"WalkU", srcTex, 8, Vector2(0, texSize.y * 0.2f), Vector2(texSize.x * 0.8f, texSize.y * 0.3f ), 1.0f / 10.0f);
	AnimationClip* WalkD = new AnimationClip(L"WalkD", srcTex, 8, Vector2(0, texSize.y * 0.3f), Vector2(texSize.x * 0.8f, texSize.y * 0.4f ), 1.0f / 10.0f);

	// Attack Anim
	AnimationClip* AttackL = new AnimationClip(L"AttackL", srcTex, 6, Vector2(0, texSize.y * 0.7f), Vector2(texSize.x * 0.6f, texSize.y * 0.8f), 1.0f / 20.0f, true);
	AnimationClip* AttackR = new AnimationClip(L"AttackR", srcTex, 6, Vector2(0, texSize.y * 0.6f), Vector2(texSize.x * 0.6f, texSize.y * 0.7f), 1.0f / 20.0f);
	AnimationClip* AttackU = new AnimationClip(L"AttackU", srcTex, 5, Vector2(0, texSize.y * 0.5f), Vector2(texSize.x * 0.5f, texSize.y * 0.6f), 1.0f / 20.0f);
	AnimationClip* AttackD = new AnimationClip(L"AttackD", srcTex, 5, Vector2(0, texSize.y * 0.4f), Vector2(texSize.x * 0.5f, texSize.y * 0.5f), 1.0f / 20.0f);

	// skill Anim
	

	// win Pos

	// death Pos


	//clip save
	animator->SetAnim(IdleR);
	animator->SetAnim(IdleL);
	animator->SetAnim(IdleU);
	animator->SetAnim(IdleD);
	animator->SetAnim(WalkR);
	animator->SetAnim(WalkL);
	animator->SetAnim(WalkU);
	animator->SetAnim(WalkD);
	animator->SetAnim(AttackL);
	animator->SetAnim(AttackR);
	animator->SetAnim(AttackU);
	animator->SetAnim(AttackD);




	//arrow class
	

	animator->SetCurrentAnimClip(L"IdleR");
	
	
	animRect->SetAnimation(animator);
	


	//collision edge
	SetCollision(20, 20, 20, 20);

	animRect->SetHp(100);
	animRect->SetAttack(5);
	animRect->SetisLive(true);


	SAFE_DELETE(srcTex);
}

Player::~Player()
{
	SAFE_DELETE(HP1);
	SAFE_DELETE(HP2);
	
}

void Player::Update()
{
	
	
	animator->Update();
	animRect->Update();
	animRect->Move();
	
	Vector3 tmp = *(animRect->GetPos());
	tmp.y -= 30;

	HP2->Sethpint(animRect->GetHp());

	HP1->SetPosition(tmp);
	HP2->SetPosition(tmp);
	HP1->Update();
	HP2->Update();
	


	

	


}

void Player::Render()
{
	


	
	animRect->Render();
	HP1->Render();
	HP2->Render();
}


