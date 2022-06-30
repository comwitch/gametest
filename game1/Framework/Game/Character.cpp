#include "Framework.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size)
{
	animRect = new AnimationRect(position, size);
	animator = new Animator();
	

}

Character::~Character()
{
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
}

void Character::SetCollision(float LT_x, float LT_y, float RB_x, float RB_y)
{
	animRect->SetCollisionLT(LT_x, LT_y);
	animRect->SetCollisionRB(RB_x, RB_y);
}

Vector3* Character::GetPosition()
{
	return animRect->GetPos();
}