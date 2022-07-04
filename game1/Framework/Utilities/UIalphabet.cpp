#include "Framework.h"
#include "UIalphabet.h"

UIClip::UIClip(wstring clipName, Texture2D * srcTex, Vector2 startPos, Vector2 endPos)
	:clipName(clipName)
{
	srv = srcTex->GetSRV();  //�̹��� �ҽ��� �����ͼ� ����

	float imageWidth = srcTex->GetWidth();		//���� ����ϴ� �̹����� ����ũ�� ���ϱ�
	float imageHeight = srcTex->GetHeight();	//���� ����ϴ� �̹����� ����ũ�� ���ϱ�

	Vector2 clipSize = endPos - startPos;		//���� ����� Ŭ���� ������ ���ϱ�
	Vector2 frameSize;
	frameSize.x = clipSize.x;		//���������� ����� ���ϱ�
	frameSize.y = clipSize.y;

	texelFrameSize.x = frameSize.x / imageWidth;	//�ϳ��� �ؼ� ũ�⸦ ���ϱ�
	texelFrameSize.y = frameSize.y / imageHeight;

	
	texelStartPos.x = startPos.x / imageWidth;		//�ϳ��� �ؼ��� �������� ���ϱ�
	texelStartPos.y = startPos.y / imageHeight;


}

UIalphabet::UIalphabet()
{
}

UIalphabet::~UIalphabet()
{
	for (auto clip : UIclips)
		SAFE_DELETE(clip.second);
}

void UIalphabet::Update()
{

}

void UIalphabet::AddUIClip(UIClip * UIClip)
{
	UIclips.insert(make_pair(UIClip->clipName, UIClip));
}

void UIalphabet::SetCurrentUIClip(wstring clipName)
{
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = UIclips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipName != clipName)
		currentClip = UIclips.find(clipName)->second;
	else if (currentClip->clipName == clipName)
		return;

	
	if (CheckExist(clipName))
	{
		currentClip = UIclips.find(clipName)->second;
		currentFrame = currentClip->texelStartPos;
	}
}

void UIalphabet::SetUI(UIClip * clip)
{
	
		
		AddUIClip(clip);
	
	
}
