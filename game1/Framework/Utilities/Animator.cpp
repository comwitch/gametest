#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D * srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bReversed)
	:clipName(clipName), frameCount(frameCount), playRate(playRate), bReversed(bReversed)
{
	srv = srcTex->GetSRV();  //이미지 소스를 가져와서 대입

	float imageWidth = srcTex->GetWidth();		//현재 사용하는 이미지의 가로크기 구하기
	float imageHeight = srcTex->GetHeight();	//현재 사용하는 이미지의 세로크기 구하기

	Vector2 clipSize = endPos - startPos;		//현재 사용할 클립의 사이즈 구하기
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;		//한프레임의 사이즈를 구하기
	frameSize.y = clipSize.y;

	texelFrameSize.x = frameSize.x / imageWidth;	//하나의 텍셀 크기를 구하기
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;		//하나의 텍셀의 시작점을 구하기
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyframe;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
		keyframe.y = texelStartPos.y;
		keyFrames.push_back(keyframe);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
		SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (deltaTime > currentClip->playRate)
	{
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++;

			if (currentFrameIndex == currentClip->frameCount)
			{
				Rate = Time::Delta();
				currentFrameIndex = 0;
			}

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else
		{
			currentFrameIndex--;

			if (currentFrameIndex == -1)
				currentFrameIndex = currentClip->frameCount - 1;

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}
	else
	{
		deltaTime += Time::Delta();
	}
}

void Animator::AddAnimClip(AnimationClip * animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = animClips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipName != clipName)
		currentClip = animClips.find(clipName)->second;
	else if (currentClip->clipName == clipName)
		return;

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		deltaTime = 0.0f;

		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}

void Animator::SetAnim(AnimationClip * clip)
{
	
		
		AddAnimClip(clip);
	
	
}
