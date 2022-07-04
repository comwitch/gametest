#pragma once

#include "Geomatries/UIRect.h"
#include "Utilities/UIalphabet.h"


class UI 
{
public:
	UI(Vector3 position, Vector3 size, int mode);
	~UI();

	void init_startUI();
	void init_pauseUI();
	void init_time();
	


	void Update() ;
	void Render() ;
	UIRect* GetanimRect() { return animRect; }

	//for helloworld
	void UpdateStart();
	void RenderStart();
	
	//for Time UI
	void UpdateTime(int _time);
	void RenderTime();


	int GetPressWhat() { return pressWhat; }



private:

	Vector3 position;
	Vector3 size;
	int mode = 0;  // mode 0 은 게임시작 1 은 ui 시간관련함수 2 는 pause관련 3은 레벨업 관련


	//시간 관련 
	class UIRect* Time1 = nullptr;
	class UIRect* Time2 = nullptr;
	class UIRect* Time3 = nullptr;
	class UIRect* Time4 = nullptr;

	//레벨업 창 관련

	//게임 시작 관련
	class UITextureRect* start = nullptr;
	class UITextureRect* how = nullptr;




	UIRect* animRect = nullptr;
	UIalphabet* Timealphabet1 = nullptr;
	UIalphabet* Timealphabet2 = nullptr;
	UIalphabet* Timealphabet3 = nullptr;
	UIalphabet* Timealphabet4 = nullptr;

	int pressWhat = 0;
	int time = 0;
};