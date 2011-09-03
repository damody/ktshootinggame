#pragma once
#include "ball.h"
#include "behavior.h"
#include "math/OgreVector3.h"

class Homing : public Behavior
{	
public:
	float	mVelocity;
	Ogre::Vector3	(*GetEnemyPos)();
	GET_CLASS_SIZE(Homing)
	inline Homing()
	{m_typehash = strhasher("Homing");}
	virtual int UpdateBall(Ball* b, float elapsedtime);
	virtual ~Homing()
	{}
};