#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"
#include "planes/MainPlane.h"

class Gravity : public Behavior
{
public:
	float		mVelocity;
	Ogre::Vector3	mForce;
	Ogre::Vector3	mGravity;
public:
	inline Gravity():mVelocity(1.0f)
	{}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Gravity()
	{}
};