#pragma once
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include "algo/sgmath.h"
#include "math/OgreVector3.h"
#include "common/utility.h"
#include "behavior.h"
#include "math/Polygon2D.h"
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
	// Ogre::Vector3	mUp;  // no use
	Polygon2D	mPolygon2D;
	float		mTimeRate;
	Behavior*	mpBehavior;
	BallStatus	mBallStatus;
	int		mCollisionMask;
public:
	VIRTUAL_GET_CLASS_SIZE(Behavior)
	inline Ball():mTimeRate(1), mCollisionMask(1)
	{
	}
	inline Ball(const Ogre::Vector3 pos, const Ogre::Vector3 dir, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(dir), mCollisionMask(1),
		//mUp(Ogre::Vector3::NEGATIVE_UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY)
	{
	}
	inline Ball(const Ogre::Vector3 pos, float angle, Behavior* behavior = NULL)
		:mTimeRate(1), mPosition(pos), mDirection(GetRotation(pos, angle)), 
		//mUp(Ogre::Vector3::NEGATIVE_UNIT_Z), 
		mpBehavior(behavior), mBallStatus(FLY), mCollisionMask(1)
	{
	}
	virtual int Update(float elapsedtime);
	bool HasBehavior();
	virtual ~Ball()
	{}
	Ball(const Ball& b)
	{
		*this = b;
	}
};
// TODO: typedef Ball* (*NewBallFunction)(void*);
typedef Ball* (*NewBallFunction)();
typedef std::vector<Ball> BallVector;
typedef std::list<Ball> BallList;
typedef std::vector<Ball*> BallptrVector;

