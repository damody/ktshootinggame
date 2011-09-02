#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

class Delay : public Behavior
{
public:
	float mElapsedTime;
	float mLaunchTime;
	float mVelocity;

	inline Delay()
	{m_typehash = strhasher("Delay");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Delay()
	{}
};