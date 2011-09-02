#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

typedef struct HomingData
{
	float	mVelocity;
	Ogre::Vector3	(*GetEnemyPos)();
}HomingData;

class Homing : public Behavior
{	
public:
	inline Homing()
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Homing()
	{}
};