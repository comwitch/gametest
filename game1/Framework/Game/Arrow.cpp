#include "Framework.h"
#include "Arrow.h"

Arrow::Arrow(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"arrow.png"); // 이미지 소스

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());


	// idle Anim
	AnimationClip* IdleU = new AnimationClip(L"IdleU", srcTex, 1, Vector2(0, 0), Vector2(texSize.x * 0.5f, texSize.y), 1.0f / 15);
	AnimationClip* IdleD = new AnimationClip(L"IdleD", srcTex, 1, Vector2(texSize.x * 0.5f, texSize.y), Vector2(0, 0), 1.0f / 15);
	AnimationClip* IdleR = new AnimationClip(L"IdleR", srcTex, 1, Vector2(texSize.x*0.5, 0), Vector2(texSize.x, texSize.y), 1.0f / 15);
	AnimationClip* IdleL = new AnimationClip(L"IdleL", srcTex, 1, Vector2(texSize.x, texSize.y), Vector2(texSize.x*0.5, 0), 1.0f / 15);


	//arrowchecker
	animRect->SetCharacter(2);

	animator->SetAnim(IdleL);
	animator->SetAnim(IdleR);
	animator->SetAnim(IdleU);
	animator->SetAnim(IdleD);

	animator->SetCurrentAnimClip(L"IdleR");
	

	animRect->SetAnimation(animator);


	//충돌 범위를 조정시키는 함수
	SetCollision(28, 22, 20, 28);


	SAFE_DELETE(srcTex);
	


}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	animator->Update();
	animRect->Update();

}

void Arrow::Render()
{
	animRect->Render();
}
