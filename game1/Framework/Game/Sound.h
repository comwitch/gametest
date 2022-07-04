#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player(Vector3 position, Vector3 size);
	~Player();

	virtual void Update() override;
	virtual void Render() override;
	AnimationRect* GetanimRect() { return animRect; }

	
	
	




private:

	


	class HPRect* HP1 = nullptr;
	class HPRect* HP2 = nullptr;

};