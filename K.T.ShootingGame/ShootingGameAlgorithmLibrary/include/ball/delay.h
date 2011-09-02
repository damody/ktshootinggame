#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

typedef struct DelayData
{
	float mElapsedTime;
	float mLaunchTime;
	float mVelocity;
}DelayData;

class Delay : public Behavior
{
public:
	inline Delay()
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Delay()
	{}
};