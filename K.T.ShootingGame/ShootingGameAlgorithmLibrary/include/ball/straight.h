#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

class Straight : public Behavior
{
public:
	float	mVelocity;
	inline Straight()
	{m_typehash = strhasher("Straight");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Straight()
	{}
};


