#pragma once
#include "algo/sgmath.h"
#include "math/OgreVector3.h"
#include "common/utility.h"
#include "behavior.h"
#include <vector>
#include <list>

class Ball
{
public:
	enum BallStatus
	{
		FLY,
		STOP,
		DESTORY
	};
	Ogre::Vector3	mPosition;
	Ogre::Vector3	mDirection;
	Ogre::Vector3	mUp;
	float		mTimeRate;
	Behavior*	mpBehavior;
	BallStatus	mBallStatus;
public:
	GET_CLASS_SIZE(Ball)
	inline Ball():mTimeRate(1)
	{
	}
	inline Ball(const Ogre::Vector3 pos, const Ogre::Vector3 dir, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(dir), mUp(Ogre::Vector3::UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY)
	{
	}
	inline Ball(const Ogre::Vector3 pos, float angle, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(GetRotation(pos, Ogre::Vector3::UNIT_Z, angle)), mUp(Ogre::Vector3::UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY)
	{
	}
	int Update(float elapsedtime);
	bool HasBehavior();
};
typedef std::vector<Ball> BallVector;
typedef std::list<Ball> BallList;
