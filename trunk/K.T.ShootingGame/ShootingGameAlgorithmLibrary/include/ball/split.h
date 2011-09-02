#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

struct SplitData
{
	float	mVelocity;
	float	mAngle;
	float	mMaxAngle;
	float	mOAngle;
};

class Split : public Behavior
{
public:
	inline Split()
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Split()
	{}
};