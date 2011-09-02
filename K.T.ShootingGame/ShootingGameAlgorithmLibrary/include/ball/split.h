#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

class Split : public Behavior
{
public:
	float	mVelocity;
	float	mAngle;
	float	mMaxAngle;
	float	mOAngle;
public:
	inline Split():mVelocity(1.0f), mAngle(0), mMaxAngle(0)
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Split()
	{}
};