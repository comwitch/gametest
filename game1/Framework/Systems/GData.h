#pragma once

// GData : ���ӿ��� ĳ���Ϳ� ���� ������ �������� ���� ���� Ŭ����.



class GData : public SingletonBase<GData>
{
public:
	friend class SingletonBase<GData>;

	int Getcfacing() { return cfacing; }
	void Setcfacing(int _cfacing) { this->cfacing = _cfacing; }
	

	



private:
	GData();
	~GData();
	
	int cfacing = 0;
	
};