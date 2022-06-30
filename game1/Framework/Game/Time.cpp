#include "Framework.h"
#include "Time.h"
#include "Game/Arrow.h"
#include "Geomatries/HPRect.h"




Time::Time(Vector3 position, Vector3 size)
	
{

	animRect = new AnimationRect(position, size);
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"chmov.png"); // 이미지 소스

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());


	
	

	
	// idle Anim
	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 1, Vector2(0, texSize.y*0.1), Vector2(texSize.x * 0.1f, texSize.y*0.2f), 1.0f / 15);
	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 1, Vector2(0, 0), Vector2(texSize.x * 0.1f, texSize.y * 0.1f), 1.0f / 10.0f);
	AnimationClip* IdleU = new AnimationClip(L"IdleU", srcTex, 1, Vector2(0, texSize.y*0.2), Vector2(texSize.x * 0.1f, texSize.y * 0.3f), 1.0f / 10.0f);
	AnimationClip* IdleD = new AnimationClip(L"IdleD", srcTex, 1, Vector2(0, texSize.y*0.3), Vector2(texSize.x * 0.1f, texSize.y * 0.4f), 1.0f / 10.0f);

	//clip save
	animator->SetAnim(IdleR);
	animator->SetAnim(IdleL);
	animator->SetAnim(IdleU);
	animator->SetAnim(IdleD);





	//arrow class
	

	animator->SetCurrentAnimClip(L"IdleL");
	
	
	animRect->SetAnimation(animator);
	







	SAFE_DELETE(srcTex);
}

Time::~Time()
{

	
}

void Time::Update()
{
	
	
	animator->Update();
	animRect->Update();
	animRect->Move();

}

void Time::Render()
{
	


	
	animRect->Render();

}


