#pragma once
#define MAXMONSTER 13
#define PoolSize 13



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

private:
	class TextureRect2* Gamemap = nullptr;
	class Player* player = nullptr;

	vector<class Enemy*> EnemyPool;
	class Arrow* arrow = nullptr;

	class UI* timeUI = nullptr;

	class Collisionengine* engine = nullptr;

	class CSound* Sound = nullptr;

	int play = 0;
	float time = 0.0f;
	float timechecker = 0.0f;


	bool Valid = true;

	int PauseCount = 0;
	int PoolCount = 0;

	int deathCount = 0;
	

};