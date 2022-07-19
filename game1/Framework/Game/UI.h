#pragma once

#include "Geomatries/UIRect.h"
#include "Utilities/UIalphabet.h"


class UI 
{
public:
	/* 
	mode 0 �� ���ӽ��� 1 �� ui �ð������Լ� 2 �� pause���� 3�� ������ ���� 4�� �¸� �� �й���� 5�� ���ӳ��� ui
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
	int mode = 0;  // mode 0 �� ���ӽ��� 1 �� ui �ð������Լ� 2 �� pause���� 3�� ������ ���� 4�� �¸� �� �й����


	//�ð� ���� 
	class UIRect* Time1 = nullptr;
	class UIRect* Time2 = nullptr;
	class UIRect* Time3 = nullptr;
	class UIRect* Time4 = nullptr;

	//������ â ����
	class TextureRect2* Levelup = nullptr;
	
	class UITextureRect* attackup = nullptr;
	class UITextureRect* HPup = nullptr;
	class UITextureRect* attackspeedup = nullptr;




	//���� ���� ����
	class UITextureRect* start = nullptr;
	class UITextureRect* how = nullptr;
	class TextureRect2* howto = nullptr;

	//�¸� �й� UI ����
	class TextureRect2* winUI = nullptr;
	class TextureRect2* LoseUI = nullptr;

	//����UI ����
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
	������ UI �� ������ �޾Ƶ鿴���� �޽����� �����µ� ���� ���� ���� �ٸ��뵵�� ���δ�

	time UI : nothing (�Ⱦ���)

	startUI : demo���Ͽ� �������� ������ �ȳѱ����� ���� ����ϴ� �뵵 (1: �ѱ� 0: �ȳѱ�)

	levelupUI : ���ӿ��� �̻���� ���������� ���� �ɷ�ġ�� ����Ͽ����� �˷��ִ� ����(0: �״�� , 1 : hpup 2: attackup 3: attackspeedUP
	*/
	
	
	bool howtoUI = false;
	int time = 0;
};