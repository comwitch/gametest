#pragma once

#include "Geomatries/UIRect.h"
#include "Utilities/UIalphabet.h"


class UI 
{
public:
	/* 
	mode 0 은 게임시작 1 은 ui 시간관련함수 2 는 pause관련 3은 레벨업 관련 4는 승리 및 패배관련 5는 게임내부 ui
	*/
	UI(Vector3 position, Vector3 size, int mode);
	~UI();

	void init_startUI();
	void init_pauseUI();
	void init_levelupUI();
	void init_time();
	void init_result();
	void init_gameUI();
	void init_NumstartUI();
	


	void Update() ;
	void Render() ;
	UIRect* GetanimRect() { return animRect; }

	//for helloworld
	void UpdateStart();
	void RenderStart();
	
	//for levelup

	void UpdateLevelup();
	void RenderLevelup();

	//for Time UI
	void UpdateTime(int _time);
	void RenderTime();


	//result UI
	void UpdateWin();
	void UpdateLose();
	void RenderWin();
	void RenderLose();

	//for Game UI
	void UpdategameUI(int LVcount, int ATcount, int AScount);
	void RendergameUI();

	//for NumStartUi

	void UpdateNumstartUI(int _time);
	void RenderNumstartUI();


	int GetPressWhat() { return pressWhat; }
	void SetPressWhat(int a) { this->pressWhat = a; }



private:

	Vector3 position;
	Vector3 size;
	int mode = 0;  // mode 0 은 게임시작 1 은 ui 시간관련함수 2 는 pause관련 3은 레벨업 관련 4는 승리 및 패배관련


	//시간 관련 
	class UIRect* Time1 = nullptr;
	class UIRect* Time2 = nullptr;
	class UIRect* Time3 = nullptr;
	class UIRect* Time4 = nullptr;

	//레벨업 창 관련
	class TextureRect2* Levelup = nullptr;
	
	class UITextureRect* attackup = nullptr;
	class UITextureRect* HPup = nullptr;
	class UITextureRect* attackspeedup = nullptr;




	//게임 시작 관련
	class UITextureRect* start = nullptr;
	class UITextureRect* how = nullptr;
	class TextureRect2* howto = nullptr;

	//승리 패배 UI 관련
	class TextureRect2* winUI = nullptr;
	class TextureRect2* LoseUI = nullptr;

	//게임UI 관련
	class TextureRect2* gameUI = nullptr;
	class UIRect* levelupcount = nullptr;
	class UIRect* levelupcount2 = nullptr;
	class UIRect* attackcount = nullptr;
	class UIRect* attackcount2 = nullptr;
	class UIRect* attackspeedcount = nullptr;
	class UIRect* attackspeedcount2 = nullptr;



	UIalphabet* gameUIalphabet1 = nullptr;
	UIalphabet* gameUIalphabet2 = nullptr;
	UIalphabet* gameUIalphabet3 = nullptr;
	UIalphabet* gameUIalphabet4 = nullptr;
	UIalphabet* gameUIalphabet5 = nullptr;
	UIalphabet* gameUIalphabet6 = nullptr;


	



	UIRect* animRect = nullptr;
	UIalphabet* Timealphabet1 = nullptr;
	UIalphabet* Timealphabet2 = nullptr;
	UIalphabet* Timealphabet3 = nullptr;
	UIalphabet* Timealphabet4 = nullptr;

	int pressWhat = 0;
	/*
	각각의 UI 가 무엇을 받아들였는지 메시지를 보내는데 쓰는 변수 각각 다른용도로 쓰인다

	time UI : nothing (안쓰임)

	startUI : demo파일에 다음으로 넘질지 안넘길지에 대해 사용하는 용도 (1: 넘김 0: 안넘김)

	levelupUI : 게임에게 이사람이 레벨업으로 무슨 능력치를 사용하였는지 알려주는 변수(0: 그대로 , 1 : hpup 2: attackup 3: attackspeedUP
	*/
	
	
	bool howtoUI = false;
	int time = 0;
};