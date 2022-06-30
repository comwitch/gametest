#pragma once

class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bReversed = false);

private:
	wstring clipName = L"";
	vector<Vector2> keyFrames;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	float playRate = 0.0f;
	bool bReversed = false;
};

class Animator
{
public:
	Animator();
	~Animator();

	void Update();
	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

	void AddAnimClip(AnimationClip* animClip);
	void SetCurrentAnimClip(wstring clipName);
	AnimationClip* GetCurrentClip() { return currentClip; }

	void SetAnim(AnimationClip* clip);

private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }

	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.0f;

	AnimationClip* idleL = nullptr;
	AnimationClip* idleR = nullptr;
	AnimationClip* moveLeft = nullptr;
	AnimationClip* moveRight = nullptr;
	AnimationClip* moveUp = nullptr;
	AnimationClip* moveDown = nullptr;
	AnimationClip* jumpL = nullptr;
	AnimationClip* jumpR = nullptr;
	AnimationClip* sprintR = nullptr;
	AnimationClip* sprintL = nullptr;
	AnimationClip* actionR = nullptr;
	AnimationClip* actionL = nullptr;
	AnimationClip* skill1 = nullptr;
	AnimationClip* skill2 = nullptr;

	float Rate = 0.0f;
};