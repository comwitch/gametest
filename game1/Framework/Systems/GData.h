#pragma once

// GData : 게임에서 캐릭터에 대한 정보를 가져오기 위해 만든 클래스.



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