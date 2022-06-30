#pragma once

class OBBDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class OBBRect* ob1 = nullptr;
	class OBBRect* ob2 = nullptr;
};