#pragma once
#include "ball.h"
#include "behavior.h"
#include "../math/OgreVector3.h"

class Straight : public Behavior
{
public:
	float	mVelocity;
public:
	inline Straight():mVelocity(1.0f)
	{}
	void SetVector(float v);
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Straight()
	{}
};

