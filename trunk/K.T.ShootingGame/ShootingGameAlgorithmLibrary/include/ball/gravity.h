#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

typedef struct GravityData
{
	Ogre::Vector3	mVelocity;
	Ogre::Vector3	mForce;
	Ogre::Vector3	mGravity;
}GravityData;

class Gravity : public Behavior
{
public:
	inline Gravity()
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Gravity()
	{}
};