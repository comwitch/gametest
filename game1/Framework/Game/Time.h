#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"


class Time 
{
public:
	Time(Vector3 position, Vector3 size);
	~Time();

	void Update() ;
	void Render() ;
	AnimationRect* GetanimRect() { return animRect; }

	
	
	




private:

	AnimationRect* animRect = nullptr;
	Animator* animator = nullptr;


};