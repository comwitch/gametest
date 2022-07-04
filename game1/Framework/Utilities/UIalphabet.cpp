#include "Framework.h"
#include "UIalphabet.h"

UIClip::UIClip(wstring clipName, Texture2D * srcTex, Vector2 startPos, Vector2 endPos)
	:clipName(clipName)
{
	srv = srcTex->GetSRV();  //이미지 소스를 가져와서 대입

	float imageWidth = srcTex->GetWidth();		//현재 사용하는 이미지의 가로크기 구하기
	float imageHeight = srcTex->GetHeight();	//현재 사용하는 이미지의 세로크기 구하기

	Vector2 clipSize = endPos - startPos;		//현재 사용할 클립의 사이즈 구하기
	Vector2 frameSize;
	frameSize.x = clipSize.x;		//한프레임의 사이즈를 구하기
	frameSize.y = clipSize.y;

	texelFrameSize.x = frameSize.x / imageWidth;	//하나의 텍셀 크기를 구하기
	texelFrameSize.y = frameSize.y / imageHeight;

	
	texelStartPos.x = startPos.x / imageWidth;		//하나의 텍셀의 시작점을 구하기
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
