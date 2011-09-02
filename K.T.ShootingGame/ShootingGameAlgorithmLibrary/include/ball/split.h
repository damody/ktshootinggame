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

	inline Split()
	{m_typehash = strhasher("Split");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Split()
	{}
};