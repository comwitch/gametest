#pragma once

#include "Character.h"

class Arrow : public Character
{
public:
	Arrow(Vector3 position, Vector3 size);
	~Arrow();


	virtual void Update() override;
	virtual void Render() override;

	AnimationRect* GetanimRect() { return animRect; }
	void SetPlayerPos(Vector3 pos) { this->animRect->SetPos(pos); }


private:
	Vector3* PlayerPos = nullptr;
	int FacingWhere = 0;
};