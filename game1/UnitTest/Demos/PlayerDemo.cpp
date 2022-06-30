#include "stdafx.h"
#include "PlayerDemo.h"
#include "Game/enemy.h"
#include "Game/Player.h"
#include "Game/Arrow.h"
#include "Geomatries/TextureRect2.h"


void PlayerDemo::Init()
{
	Camera::Create();
	Gamemap = new TextureRect2({ 640,360,0 }, Vector3(2 * WinMaxWidth, 2 * WinMaxHeight, 1), 0.0f, TexturePath + L"bg_green.png");
	
	player = new Player({ 640, 360, 0 }, { 100, 100, 1 });

	arrow = new Arrow({ 0,0,1 }, { 50,50,1 });

	Vector3 * position22 = player->GetanimRect()->GetPos();

	engine = new Collisionengine();

	engine->insert((player->GetanimRect()->GetBox()), (player->GetanimRect()->GetPos()), player->GetanimRect(), 1);

	engine->insert((arrow->GetanimRect()->GetBox()), (arrow->GetanimRect()->GetPos()), arrow->GetanimRect(), 3);


	
	for (int i  = 0 ; i < PoolSize ; i++)
	{
		int tmp_X = rand() % 1280;
		int tmp_Y = rand() % 720;
		EnemyPool.push_back(new Enemy({ (float)tmp_X, (float)tmp_Y, 1 }, { 100, 100, 1 }));
		engine->insert(EnemyPool[i]->GetanimRect()->GetBox(), EnemyPool[i]->GetanimRect()->GetPos(), EnemyPool[i]->GetanimRect(), 2);
		
	}


	
	Time::Create();
	

	
	
}
void PlayerDemo::Destroy()
{


	SAFE_DELETE(engine);
	SAFE_DELETE(Gamemap);
	SAFE_DELETE(arrow);
	
	vector<class Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		SAFE_DELETE(*iter);

	}
	EnemyPool.clear();


}

void PlayerDemo::Update()
{
	//�ð�������Ʈ
	time += Time::Delta();
	timechecker += Time::Delta();

	//�÷��̾ �׾��� �� �װ� ���� ���������� ����
	if (player->GetanimRect()->GetHp() <= 0)
	{
		this->Destroy();
		this->Init();
		Valid = false;
	}


	//�Ͻ����� ����
	if (Keyboard::Get()->Down('P'))
	{
		if (PauseCount == 0)
		{
			PauseCount++;
			Time::Get()->Stop();
		}
		else
		{
			PauseCount--;
			Time::Get()->Start();
		}
	}
		
	
		

	// ���� �� ������Ʈ
	Gamemap->Update();

	//ȭ�� ������Ʈ
	if (timechecker > 1.0f)
	{
		arrow->SetPlayerPos(*player->GetPosition());
		arrow->GetanimRect()->SetisLive(true);
		arrow->Update();
		timechecker = 0;
	}
	if (arrow->GetanimRect()->GetisLive() == true)
		arrow->Update();


	// player ������Ʈ
	player->Update();


	// enemy ������Ʈ
	vector<class Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		if ((*iter)->GetanimRect()->GetisLive() == true)
		{
			(*iter)->Update();

		}
		if ((*iter)->GetanimRect()->GetisLive() == false)
		{
			
		}
			
		(*iter)->Gettargetposition(*(player->GetanimRect()->GetPos()));
	}


	// collision ������Ʈ
	engine->Update();



	


}

void PlayerDemo::Render()
{
	
	
	Gamemap->Render();

	player->Render();

	vector<Enemy*>::iterator iter = EnemyPool.begin();
	for (; iter != EnemyPool.end(); iter++)
	{
		if ((*iter)->GetanimRect()->GetisLive() == true)
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
