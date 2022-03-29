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
�� �˰���

1. �̹��� �ҽ��� ���� �޴´�.
2. �̹����� �ٿ���ø��� �Ѵ�.
3. ���� ��
4. ���� ��
5. �̹����� ���� ũ��� �ǵ�����.
*/