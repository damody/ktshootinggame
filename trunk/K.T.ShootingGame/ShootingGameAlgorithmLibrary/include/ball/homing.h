#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"
#include "planes/MainPlane.h"

class Homing : public Behavior
{
public:
	float	mVelocity;
	Ogre::Vector3	(*GetEnemyPos)();
public:
	inline Homing():mVelocity(1.0f)
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Homing()
	{}
};