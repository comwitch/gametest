#pragma once

class RTTDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class RenderTexture* rtt = nullptr;
	class TextureRect* rt1 = nullptr;
	class TextureRect* rt2 = nullptr;
	class Rect* r1 = nullptr;
	class Rect* r2 = nullptr;
	class Rect* r3 = nullptr;
};