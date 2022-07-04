#pragma once

class TextureDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;
	virtual bool IsValid() override;
	virtual void SetIsValid(bool _valid) override ;
	
private:
	class TextureRect2* tr = nullptr;
	class UI* startUI = nullptr;

	
	bool Valid = true;

	
	


	
	

};