#pragma once

class IObject
{
public:
	virtual void Init()			= 0; 
	virtual void Destroy()		= 0;	// �Ҹ��� ��ü

	virtual void Update()		= 0; 
	
	virtual void Render()		= 0;
	virtual void PostRender()	= 0;	// ��ó���� �ʿ��� �ڵ带 ó��
	virtual bool IsValid()		= 0;	// �ش� demo�� ������ ���� ������ �ִ��� Ȯ��
	virtual void SetIsValid(bool _valid) = 0;


	virtual void GUI()			= 0;	// �ܺ� ���̺귯��



};