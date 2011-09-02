#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

struct StraightData
{
	float	mVelocity;
};

class Straight : public Behavior
{
public:
	inline Straight()
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Straight()
	{}
};

