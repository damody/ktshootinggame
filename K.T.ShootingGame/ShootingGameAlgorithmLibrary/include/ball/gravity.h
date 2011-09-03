#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

class Gravity : public Behavior
{
public:
	Ogre::Vector3	mVelocity;
	Ogre::Vector3	mForce;
	Ogre::Vector3	mGravity;
	GET_CLASS_SIZE(Gravity)
	inline Gravity()
	{m_typehash = strhasher("Gravity");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Gravity()
	{}
};