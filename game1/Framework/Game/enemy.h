#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(Vector3 position, Vector3 size);
	~Enemy();

	virtual void Update() override;
	virtual void Render() override;


	void Gettargetposition(Vector3 tp) { animRect->targetpostiont = tp; }
	AnimationRect* GetanimRect() { return animRect; }
	
	float Getdietime() { return dietime; }
	void Setdietime() { this->dietime = 0.0f; }




private:
	Vector3 targetposition = { 0, 0, 0 };
	float dietime = 0.0f;


};