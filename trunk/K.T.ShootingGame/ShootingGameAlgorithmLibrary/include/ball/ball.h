#pragma once
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
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
		DESTORY // if on this status, system will delete this ball
	};
	Ogre::Vector3	mPosition;
	Ogre::Vector3	mDirection;
	Ogre::Vector3	mUp;
	float		mTimeRate;
	Behavior*	mpBehavior;
	BallStatus	mBallStatus;
	unsigned char*	mData;
public:
	GET_CLASS_SIZE(Ball)
	inline Ball():mTimeRate(1)
	{
	}
	inline Ball(const Ogre::Vector3 pos, const Ogre::Vector3 dir, int nByte, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(dir), mUp(Ogre::Vector3::UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY)
	{
		mData = (unsigned char*)malloc(nByte * sizeof(unsigned char));
	}
	inline Ball(const Ogre::Vector3 pos, float angle, int nByte, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(GetRotation(pos, Ogre::Vector3::UNIT_Z, angle)), mUp(Ogre::Vector3::UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY)
	{
		mData = (unsigned char*)malloc(nByte * sizeof(unsigned char));
	}
	virtual int Update(float elapsedtime);
	bool HasBehavior();
	virtual ~Ball(){}
};
typedef Ball* (*NewBallFunction)();
typedef std::vector<Ball> BallVector;
typedef std::list<Ball> BallList;
typedef std::vector<Ball*> BallptrVector;
extern boost::object_pool<Ball> pool_Ball;

