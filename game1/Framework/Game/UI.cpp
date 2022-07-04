#include "Framework.h"
#include "UI.h"


#include "Geomatries/UIRect.h"
#include "Geomatries/TextureRect2.h"
#include "Geomatries/UITextureRect.h"




UI::UI(Vector3 position, Vector3 size, int mode)
	:position(position), size(size), mode(mode)
{
	if (mode == 0)
		init_startUI();
	else if (mode == 1)
		init_time();
	else if (mode == 2)
		init_pauseUI();
}

UI::~UI()
{

	
}

void UI::init_startUI()
{
	start = new UITextureRect(position, size, 0.0f, TexturePath + L"GameStart.png");
	how = new UITextureRect(position - Vector3(0, (1.3)*size.y, 0), size, 0.0f, TexturePath + L"howtoplay.png");

	
}

void UI::init_pauseUI()
{
}

void UI::init_time()
{

	Time1 = new UIRect(position, size);
	Time2 = new UIRect(position + Vector3(size.x, 0, 0), size);
	Time3 = new UIRect(position + Vector3(3 * size.x, 0, 0), size);
	Time4 = new UIRect(position + Vector3(4 * size.x, 0, 0), size);
	Timealphabet1 = new UIalphabet();

	Texture2D* srcTex = new Texture2D(TexturePath + L"number.png"); // 이미지 소스

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());



	/*

	Time UI




	*/


	// idle Anim
	UIClip* Num1 = new UIClip(L"Num1", srcTex, Vector2(texSize.x *0.8f, texSize.y* 0.167f), Vector2(texSize.x, texSize.y* 0.33f));
	UIClip* Num2 = new UIClip(L"Num2", srcTex, Vector2(texSize.x *0.2f, 0.0f), Vector2(texSize.x * 0.4f, texSize.y* 0.167f));
	UIClip* Num3 = new UIClip(L"Num3", srcTex, Vector2(texSize.x *0.4f, 0.0f), Vector2(texSize.x * 0.6f, texSize.y* 0.167f));
	UIClip* Num4 = new UIClip(L"Num4", srcTex, Vector2(texSize.x *0.6f, 0.0f), Vector2(texSize.x * 0.8f, texSize.y* 0.167f));
	UIClip* Num5 = new UIClip(L"Num5", srcTex, Vector2(texSize.x *0.8f, 0.0f), Vector2(texSize.x, texSize.y* 0.167f));
	UIClip* Num6 = new UIClip(L"Num6", srcTex, Vector2(0.0f, texSize.y* 0.167f), Vector2(texSize.x * 0.2f, texSize.y* 0.33f));
	UIClip* Num7 = new UIClip(L"Num7", srcTex, Vector2(texSize.x *0.2f, texSize.y* 0.167f), Vector2(texSize.x * 0.4f, texSize.y* 0.33f));
	UIClip* Num8 = new UIClip(L"Num8", srcTex, Vector2(texSize.x *0.4f, texSize.y* 0.167f), Vector2(texSize.x * 0.6f, texSize.y* 0.33f));
	UIClip* Num9 = new UIClip(L"Num9", srcTex, Vector2(texSize.x *0.6f, texSize.y* 0.167f), Vector2(texSize.x * 0.8f, texSize.y* 0.33f));
	UIClip* Num0 = new UIClip(L"Num0", srcTex, Vector2(0.0f, 0.0f), Vector2(texSize.x * 0.2f, texSize.y* 0.167f));

	//clip save
	Timealphabet1->SetUI(Num1);
	Timealphabet1->SetUI(Num2);
	Timealphabet1->SetUI(Num3);
	Timealphabet1->SetUI(Num4);
	Timealphabet1->SetUI(Num5);
	Timealphabet1->SetUI(Num6);
	Timealphabet1->SetUI(Num7);
	Timealphabet1->SetUI(Num8);
	Timealphabet1->SetUI(Num9);
	Timealphabet1->SetUI(Num0);





	Timealphabet1->SetCurrentUIClip(L"Num0");


	Timealphabet2 = new UIalphabet(*Timealphabet1);
	Timealphabet3 = new UIalphabet(*Timealphabet1);
	Timealphabet4 = new UIalphabet(*Timealphabet1);



	Time1->SetAnimation(Timealphabet1);
	Time2->SetAnimation(Timealphabet2);
	Time3->SetAnimation(Timealphabet3);
	Time4->SetAnimation(Timealphabet4);








	SAFE_DELETE(srcTex);
}

void UI::Update()
{
	
	
	

}

void UI::Render()
{
	


	
	animRect->Render();

}

void UI::UpdateStart()
{
	Vector2 mpos = Mouse::Get()->GetPosition();
	pressWhat = 0;
	
	
	


	if (Mouse::Get()->Press(0))
	{
		if (mpos.x < ((float)position.x + (float)(0.5)*size.x) &&
			mpos.x > ((float)position.x - (float)(0.5)*size.x) &&
			mpos.y < ((float)position.y + (float)(0.5)*size.y) &&
			mpos.y > ((float)position.y - (float)(0.5)*size.y) 
			)	
		{
			pressWhat = 1;
		}
	}
	
	start->Update();
	how->Update();
}

void UI::RenderStart()
{
	Vector2 mpos = Mouse::Get()->GetPosition();
	if (mpos.x < ((float)position.x + (float)(0.5)*size.x) &&
		mpos.x >((float)position.x - (float)(0.5)*size.x) &&
		mpos.y < ((float)position.y + (float)(0.5)*size.y) &&
		mpos.y >((float)position.y - (float)(0.5)*size.y)
		)
	{
		start->changeshaded(1);
		start->Render();
	}
	else
	{
		start->changeshaded(0);
		start->Render();
	}



	if (mpos.x < ((float)position.x + (float)(0.5)*size.x) &&
		mpos.x >((float)position.x - (float)(0.5)*size.x) &&
		mpos.y < ((float)(position.y - (1.3)*size.y) + (float)(0.5)*size.y) &&
		mpos.y >((float)(position.y - (1.3)*size.y) - (float)(0.5)*size.y)
		)
	{
		how->changeshaded(1);
		how->Render();
	}
	else
	{
		how->changeshaded(0);
		how->Render();
	}

	
}

void UI::UpdateTime(int _time)
{
	/*들어오는 시간을 분초에 맞춰서 변경후, 클립으로 바꾸는 과정*/
	
	time = _time;
	int tmptime = time % 10;
	wstring num4 = L"Num";
	num4 += to_wstring(tmptime);
	time -= tmptime;
	tmptime = time % 60;
	time -= tmptime;
	tmptime /= 10;
	wstring num3 = L"Num";
	num3 += to_wstring(tmptime);
	time /= 60;
	tmptime = time % 10;
	wstring num2 = L"Num";
	num2 += to_wstring(tmptime);
	time /= 10;
	tmptime = time % 10;
	wstring num1 = L"Num";
	num1 += to_wstring(tmptime);


	Timealphabet4->SetCurrentUIClip(num4);
	Timealphabet3->SetCurrentUIClip(num3);
	Timealphabet2->SetCurrentUIClip(num2);
	Timealphabet1->SetCurrentUIClip(num1);


	Timealphabet1->Update();
	Timealphabet2->Update();
	Timealphabet3->Update();
	Timealphabet4->Update();
	Time1->Update();
	Time2->Update();
	Time3->Update();
	Time4->Update();
}



void UI::RenderTime()
{
	Time1->Render();
	Time2->Render();
	Time3->Render();
	Time4->Render();
}


