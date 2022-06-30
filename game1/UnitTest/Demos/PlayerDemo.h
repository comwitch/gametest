#pragma once
#define MAXMONSTER	10
#define PoolSize 10



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

	class Collisionengine* engine = nullptr;

	float time = 0.0f;
	float timechecker = 0.0f;


	bool Valid = true;

	int PauseCount = 0;
	int PoolCount = 0;

	
	

};