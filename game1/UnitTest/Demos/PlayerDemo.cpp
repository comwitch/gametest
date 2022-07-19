#include "stdafx.h"
#include "PlayerDemo.h"
#include "Game/enemy.h"
#include "Game/Player.h"
#include "Game/Arrow.h"
#include "Geomatries/TextureRect2.h"
#include "Game/UI.h"
#include "Systems/Sound.h"
#include "Utilities/RenderTexture.h"
#include "Geomatries/ShadedTexture.h"



/*
init 초기화


*/
void PlayerDemo::Init()
{
	
	Camera::Create();
	
	
	rtt = new RenderTexture();
	rtt_show = new ShadedTexture(Vector3(640, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0);
	rtt_show->SetShader(ShaderPath + L"GrayScale.hlsl");

	

	//플레이관한 클래스초기화
	Gamemap = new TextureRect2({ 640,360, 0 }, Vector3(2 * WinMaxWidth, 2 * WinMaxHeight, 1), 0.0f, TexturePath + L"bg_green.png");
	player = new Player({ 640, 360, 0 }, { 100, 100, 1 });
	arrow = new Arrow({ 0,0,1 }, { 50,50,1 });
	arrow->GetanimRect()->SetAttack(130);

	Vector3 * position22 = player->GetanimRect()->GetPos();

	// 사운드 관련 초기화
	Sound = new CSound("bgm.mp3", true);
	Sound_levelup = new CSound("levelUp.mp3", true);	
	Sound_levelup->volumeDown();
	Sound_levelup->volumeDown();
	Sound_levelup->volumeDown();




	//엔진 관련 초기화
	engine = new Collisionengine();
	engine->insert((player->GetanimRect()->GetBox()), (player->GetanimRect()->GetPos()), player->GetanimRect(), 1);
	engine->insert((arrow->GetanimRect()->GetBox()), (arrow->GetanimRect()->GetPos()), arrow->GetanimRect(), 3);



	//UI 관련 초기화
	timeUI = new UI({ 560, 670, 0 }, { 40, 40, 1 }, 1);
	levelupUI = new UI({ 640, 500, 0 }, { 400, 100, 1 }, 3);
	resultUI = new UI({ 640, 500, 0 }, { 400, 100, 1 }, 4);
	gameUI = new UI(Vector3(150, 670, 0), { 400,50,1 }, 5);
	NumstartUI = new UI(Vector3(640, 360, 0), Vector3(200, 400, 1), 6);

	engine->SetEnemycount(PoolSize);
	
	//오브젝트 풀링 초기화 과정
	for (int i  = 0 ; i < PoolSize ; i++)
	{
		int tmp_X = rand() % 1280;
		int tmp_Y = rand() % 720;
		EnemyPool.push_back(new Enemy({ (float)tmp_X, (float)tmp_Y, 1 }, { 100, 100, 1 }));
		engine->insert(EnemyPool[i]->GetanimRect()->GetBox(), EnemyPool[i]->GetanimRect()->GetPos(), EnemyPool[i]->GetanimRect(), 2);
		EnemyPool[i]->GetanimRect()->SetAttack(10);
		EnemyPool[i]->GetanimRect()->SetMaxHp(50);
		EnemyPool[i]->GetanimRect()->SetHp(50);
		
	}

	*(rtt_show->GetSB()->GetSelectionPtr()) = 0;
	

	//레벨업 변수와 화살 공격속도 초기화
	levelupPoint = 10;
	attackPoint = 0;
	asPoint = 0;
	arrowtime = 2.0f;

	Time::Create();
	

	
	
}
void PlayerDemo::Destroy()
{

	SAFE_DELETE(rtt);
	SAFE_DELETE(rtt_show);
	SAFE_DELETE(engine);
	SAFE_DELETE(Gamemap);
	SAFE_DELETE(player);
	SAFE_DELETE(levelupUI);
	SAFE_DELETE(timeUI);
	SAFE_DELETE(NumstartUI);


	SAFE_DELETE(arrow);
	SAFE_DELETE(resultUI);
	vector<class Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		SAFE_DELETE(*iter);

	}
	EnemyPool.clear();

	SAFE_DELETE(engine);
	SAFE_DELETE(Sound);
	SAFE_DELETE(Sound_levelup);

}

void PlayerDemo::Update()
{
	//시간업데이트
	time += Time::Delta();
	timechecker += Time::Delta();
	Gamemap->Update();

	if (time < 3)
	{
		NumstartUI->UpdateNumstartUI(time);
	}


	else if (time > 3)
	{
		
		GameUpdate();

		//플레이어가 죽었을때
		if (player->GetanimRect()->GetHp() <= 0)
		{
			Sound->stop();
			Sound_levelup->stop();
			levelupPoint = 10; //에러방지.

			
			resultUI->UpdateLose();
			if (Keyboard::Get()->Down('S'))
			{
				time = 0.0f;
				timechecker = 0.0f;
				play = 0;
				this->Destroy();
				this->Init();
				Valid = false;
			}
		}
	}


	


}




void PlayerDemo::GameUpdate()
{
	rtt_show->Update();


	if (play == 0)
	{
		if (time < ClearTime)
		{
			Sound->play();
			play = 1;

		}
	}
	if (0< player->GetanimRect()->GetHp() && player->GetanimRect()->GetHp() < 20)
	{
		if(time < ClearTime)
			Camera::Get()->Move(time);
	}
		
	Camera::Get()->UpdateView();
	

	//일시정지 구현
	if (Keyboard::Get()->Down('P'))
	{
		if (PauseCount == 0)
		{
			PauseCount++;
			Time::Get()->Stop();
			Sound->pause();

		}
		else
		{
			PauseCount--;
			Time::Get()->Start();
			Sound->resume();
		}
	}
		
	
	
	Sound->Update();

	//플레이어가 죽었을 떄 죽고 현재 스테이지를 종료
	

	//시계 UI 구현
	timeUI->UpdateTime((int)time - 3);

	
		
	
		

	// 게임 맵 업데이트
	

	//화살 업데이트
	if (timechecker > arrowtime)
	{
		arrow->GetanimRect()->SetFacingWhere(player->GetanimRect()->GetDirection());
		arrow->SetPlayerPos(*player->GetPosition());
		arrow->GetanimRect()->SetisLive(true);
		arrow->Update();
		timechecker = 0;
	}
	if (arrow->GetanimRect()->GetisLive() == true)
		arrow->Update();


	// player 업데이트

	
	if (time < ClearTime)
	{
		player->Update();
		engine->Update();
	}
		
	


	// enemy 업데이트
	vector<class Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		
		(*iter)->Update();
		(*iter)->Gettargetposition(*(player->GetanimRect()->GetPos()));
		
		if ((*iter)->Getdietime() > 1.0f)
		{
			int tmp_X = rand() % 1280;
			int tmp_Y = rand() % 720;
			int tmp_Selection = rand() % EnemySelection;
			levelupPoint--;
			(*iter)->GetanimRect()->SetisLive(true);
			if ((int)time % 60 == 0)
			{
				(*iter)->GetanimRect()->SetMaxHp((*iter)->GetanimRect()->GetMaxHp() + 20);
			}
			(*iter)->GetanimRect()->SetHp((*iter)->GetanimRect()->GetMaxHp());
			(*iter)->Gettargetposition(*(player->GetanimRect()->GetPos()));
			(*iter)->GetanimRect()->SetPos(Vector3(tmp_X, tmp_Y, 0));
			(*iter)->GetanimRect()->SetEnemy(tmp_Selection);
			(*iter)->Setdietime();
		}
		
		
	}


	//levelup시 일어날 행동


	if (levelupPoint == 0)
	{
		
		if (PauseCount == 0)
		{
			PauseCount++;
			Time::Get()->Stop();
			Sound->pause();
			Sound_levelup->play();
		}
		
		

		levelupUI->UpdateLevelup();
		if (levelupUI->GetPressWhat() == 1)
		{
			levelupPoint = 10;
			PauseCount--;
			Time::Get()->Start();
			if (player->GetanimRect()->GetHp() + 10 > player->GetanimRect()->GetMaxHp())
				player->GetanimRect()->SetHp(player->GetanimRect()->GetMaxHp());
			else
				player->GetanimRect()->SetHp(player->GetanimRect()->GetHp() + 10);
			Sound->resume();
			levelupUI->SetPressWhat(0);
			Sound_levelup->stop();

		}
		if (levelupUI->GetPressWhat() == 2)
		{
			levelupPoint = 10;
			PauseCount--;
			Time::Get()->Start();
			player->GetanimRect()->SetAttack(player->GetanimRect()->GetAttack() + 10);
			Sound->resume();
			levelupUI->SetPressWhat(0);
			attackPoint++;
			Sound_levelup->stop();
		}
		if (levelupUI->GetPressWhat() == 3)
		{
			arrowtime = (0.9)*arrowtime;
			levelupPoint = 10;
			PauseCount--;
			Time::Get()->Start();
			Sound->resume();
			levelupUI->SetPressWhat(0);
			asPoint++;
			Sound_levelup->stop();
		}
	}

	gameUI->UpdategameUI(levelupPoint, attackPoint, asPoint);


	//클리어시 행해야할것
	if (time > ClearTime)
	{
		resultUI->UpdateWin();
		
		timechecker = 0.0f;

		play = 0;
		Sound->stop();
		
		if (Keyboard::Get()->Down('S'))
		{

			this->Destroy();
			this->Init();
			time = 0.0f;
			Valid = false;
		}

	}
	
	
	
	



	



	


}

void PlayerDemo::Render()
{
	
	Camera::Get()->Render();
	Gamemap->Render();
	
	if (time < 3)
	{
		NumstartUI->RenderNumstartUI();
	}



	if (time < ClearTime && player->GetanimRect()->GetHp() > 0 )
	{
		timeUI->RenderTime();
		if(player->GetanimRect()->GetHp() >= 0)
			player->Render();
		

		vector<Enemy*>::iterator iter = EnemyPool.begin();
		for (; iter != EnemyPool.end(); iter++)
		{
		
				(*iter)->Render();


		}




		if (arrow->GetanimRect()->GetisLive() == true)
			arrow->Render();


		if (levelupPoint == 0)
		{
			levelupUI->RenderLevelup();
		}


		gameUI->RendergameUI();
	}
	


	if (time > ClearTime)
	{
		*(rtt_show->GetSB()->GetSelectionPtr()) = 0;
		resultUI->RenderWin();
	}
	
	if (time < ClearTime && player->GetanimRect()->GetHp() <= 0)
	{
		
		*(rtt_show->GetSB()->GetSelectionPtr()) = 0;
		resultUI->RenderLose();
		


	}

	//캐릭터의 hp가 줄어들면 붉게 화면이 변하게 하는 곳
	rtt_show->SetSRV(rtt->GetSRV());
	
	if (player->GetanimRect()->GetHp() < 20)
	{
		if (*(rtt_show->GetSB()->GetSelectionPtr()) < 40)
		{
			*(rtt_show->GetSB()->GetSelectionPtr()) += 100 * Time::Delta();
		}
		if (*(rtt_show->GetSB()->GetSelectionPtr()) > 40)
		{
			*(rtt_show->GetSB()->GetSelectionPtr()) = 40;
		}

	}
	else
	{
		if (*(rtt_show->GetSB()->GetSelectionPtr()) > 0.0f)
		{
			*(rtt_show->GetSB()->GetSelectionPtr()) -= 100 * Time::Delta();
		}
		else if (*(rtt_show->GetSB()->GetSelectionPtr()) < 0.0f)
		{
			*(rtt_show->GetSB()->GetSelectionPtr()) = 0;
		}
	}
	
	rtt_show->Render();
}

void PlayerDemo::PostRender()
{
	Graphics::Get()->InitViewport();
	rtt->RenderToTexture();
	{
		Camera::Get()->Render();
		Gamemap->Render();


		if (time < ClearTime && player->GetanimRect()->GetHp() > 0)
		{
			timeUI->RenderTime();
			if (player->GetanimRect()->GetHp() >= 0)
				player->Render();


			vector<Enemy*>::iterator iter = EnemyPool.begin();
			for (; iter != EnemyPool.end(); iter++)
			{

				(*iter)->Render();


			}




			if (arrow->GetanimRect()->GetisLive() == true)
				arrow->Render();


			if (levelupPoint == 0)
			{
				levelupUI->RenderLevelup();
			}


			gameUI->RendergameUI();
		}



		if (time > ClearTime)
		{
			resultUI->RenderWin();
		}

		if (time < ClearTime && player->GetanimRect()->GetHp() <= 0)
		{

			resultUI->RenderLose();



		}

	}
	

}

void PlayerDemo::GUI()
{
	
	
}

bool PlayerDemo::IsValid()
{
	return Valid;
}

void PlayerDemo::SetIsValid(bool _valid)
{
	this->Valid = _valid;
}
