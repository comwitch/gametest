#pragma once

class Program : public IObject 
{
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	void Push(IObject* obj);

	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	vector<IObject*> objs;
	int count = 0;

	
 	

	// IObject을(를) 통해 상속됨
	virtual bool IsValid() override;


	


	// IObject을(를) 통해 상속됨
	virtual void SetIsValid(bool _valid) override;

};