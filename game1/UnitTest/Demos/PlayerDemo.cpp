#include "stdafx.h"
#include "PlayerDemo.h"
#include "Game/enemy.h"
#include "Game/Player.h"
#include "Game/Arrow.h"
#include "Geomatries/TextureRect2.h"
#include "Game/UI.h"
#include "Systems/Sound.h"


void PlayerDemo::Init()
{
	
	Camera::Create();
	Gamemap = new TextureRect2({ 640,360,0.5 }, Vector3(2 * WinMaxWidth, 2 * WinMaxHeight, 1), 0.0f, TexturePath + L"bg_green.png");
	
	player = new Player({ 640, 360, 0 }, { 100, 100, 1 });

	arrow = new Arrow({ 0,0,1 }, { 50,50,1 });
	arrow->GetanimRect()->SetAttack(30);

	Vector3 * position22 = player->GetanimRect()->GetPos();

	Sound = new CSound("bgm.mp3", true);

	engine = new Collisionengine();

	engine->insert((player->GetanimRect()->GetBox()), (player->GetanimRect()->GetPos()), player->GetanimRect(), 1);

	engine->insert((arrow->GetanimRect()->GetBox()), (arrow->GetanimRect()->GetPos()), arrow->GetanimRect(), 3);

	timeUI = new UI({ 560, 670, 0 }, { 40, 40, 1 }, 1);

	engine->SetEnemycount(PoolSize);
	
	//������Ʈ Ǯ��
	for (int i  = 0 ; i < PoolSize ; i++)
	{
		int tmp_X = rand() % 1280;
		int tmp_Y = rand() % 720;
		EnemyPool.push_back(new Enemy({ (float)tmp_X, (float)tmp_Y, 1 }, { 100, 100, 1 }));
		engine->insert(EnemyPool[i]->GetanimRect()->GetBox(), EnemyPool[i]->GetanimRect()->GetPos(), EnemyPool[i]->GetanimRect(), 2);
		EnemyPool[i]->GetanimRect()->SetAttack(10);
		
	}


	
	Time::Create();
	

	
	
}
void PlayerDemo::Destroy()
{


	SAFE_DELETE(engine);
	SAFE_DELETE(Gamemap);
	SAFE_DELETE(player);
	//SAFE_DELETE(arrow);
	
	vector<class Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		SAFE_DELETE(*iter);

	}
	EnemyPool.clear();


}

void PlayerDemo::Update()
{
	if (play == 0)
	{
		Sound->play();
		play = 1;
	}
		
	//�ð�������Ʈ
	time += Time::Delta();
	timechecker += Time::Delta();
	
	Sound->Update();

	//�÷��̾ �׾��� �� �װ� ���� ���������� ����
	if (player->GetanimRect()->GetHp() <= 0)
	{
		Sound->stop();
		this->Destroy();
		this->Init();
		Valid = false;
		time = 0.0f;
		timechecker = 0.0f;
		play = 0;
		
		
	}

	//�ð� UI ����
	timeUI->UpdateTime((int)time);

	//�Ͻ����� ����
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
		
	
		

	// ���� �� ������Ʈ
	Gamemap->Update();

	//ȭ�� ������Ʈ
	if (timechecker > 1.0f)
	{
		arrow->GetanimRect()->SetFacingWhere(player->GetanimRect()->GetDirection());
		arrow->SetPlayerPos(*player->GetPosition());
		arrow->GetanimRect()->SetisLive(true);
		arrow->Update();
		timechecker = 0;
	}
	if (arrow->GetanimRect()->GetisLive() == true)
		arrow->Update();


	// player ������Ʈ
	player->Update();
	engine->Update();
	


	// enemy ������Ʈ
	vector<class Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		
		(*iter)->Update();
		(*iter)->Gettargetposition(*(player->GetanimRect()->GetPos()));
		
		if ((*iter)->GetanimRect()->GetisLive() == false)
		{
			
			(*iter)->GetanimRect()->SetisLive(true);
			(*iter)->GetanimRect()->SetHp(100);
			(*iter)->Gettargetposition(*(player->GetanimRect()->GetPos()));
			(*iter)->GetanimRect()->SetPos(Vector3(100, 100, 0));
		}
		
		
	}

	
	
	
	



	



	


}

void PlayerDemo::Render()
{
	
	
	Gamemap->Render();

	player->Render();

	timeUI->RenderTime();

	vector<Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		if((*iter)->GetanimRect()->GetisLive() == true)
			(*iter)->Render();
		

	}
	

	
	if (arrow->GetanimRect()->GetisLive() == true)
		arrow->Render();




	

}

void PlayerDemo::PostRender()
{


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
