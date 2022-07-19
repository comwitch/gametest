#pragma once
#define PoolSize 15
#define ClearTime 60
#define EnemySelection 4



class PlayerDemo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;
	virtual bool IsValid() override;
	virtual void SetIsValid(bool _valid) override;
	void GameUpdate();


private:

	//게임플레이의 주체들
	class TextureRect2* Gamemap = nullptr;
	class Player* player = nullptr;
	vector<class Enemy*> EnemyPool;
	class Arrow* arrow = nullptr;

	//UI 관련 아래 int들은 게임에서 플레이어의 선택에 따라 달라짐
	class UI* timeUI = nullptr;
	class UI* levelupUI = nullptr;
	class UI* resultUI = nullptr;
	class UI* gameUI = nullptr;
	class UI* NumstartUI = nullptr;
	class RenderTexture* rtt = nullptr;
	class ShadedTexture* rtt_show = nullptr;
	int levelupPoint;
	int attackPoint;
	int asPoint;


	// 시스템 관련 (collision, sound, camera)
	class Collisionengine* engine = nullptr;
	VPBuffer* vpb = nullptr;
	class CSound* Sound = nullptr;
	class CSound * Sound_levelup = nullptr;
	class CSound * Sound_gameover = nullptr;
	class CSound * Sound_enemydie = nullptr;


	//플레이를 위한 시스템들 (특히 시간)
	int play = 0;
	float time = 0.0f;
	float timechecker = 0.0f;
	float arrowtime = 2.0f;
	int PauseCount = 0;

	//해당 클래스가 유효한지
	bool Valid = true;
	

	
	//test용 변수들
	int PoolCount = 0;
	int deathCount = 0;
	
	
	
};