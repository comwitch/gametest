#pragma once

class UIClip
{
public:
	friend class UIalphabet;

	UIClip(wstring clipName, Texture2D* srcTex, Vector2 startPos, Vector2 endPos);

private:
	wstring clipName = L"";
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	Vector2 texelStartPos;
};

class UIalphabet
{
public:
	UIalphabet();
	~UIalphabet();

	void Update();
	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

	void AddUIClip(UIClip* UIClip);
	void SetCurrentUIClip(wstring clipName);
	UIClip* GetCurrentClip() { return currentClip; }

	void SetUI(UIClip* clip);

private:
	unordered_map<wstring, UIClip*> UIclips;
	bool CheckExist(wstring clipName) { return UIclips.find(clipName) != UIclips.end(); }

	UIClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	
};