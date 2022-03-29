#pragma once

class BlurDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class BlurTexture* bt = nullptr;
};

/*
블러 알고리즘

1. 이미지 소스를 먼저 받는다.
2. 이미지를 다운샘플링을 한다.
3. 수평 블러
4. 수직 블러
5. 이미지를 원본 크기로 되돌린다.
*/