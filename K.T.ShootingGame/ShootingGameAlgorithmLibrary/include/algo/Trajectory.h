#pragma once
#include "math/OgreVector3.h"
#include "math/OgreQuaternion.h"
#include "ball/ball.h"
#include "ball/behavior.h"
#include "common/shared_ptr.h"

class Trajectory
{
public:
	int		mNumTrajectory;
	Ogre::Vector3	mPosition;
	Ogre::Vector3	mDirection;
	Ogre::Vector3	mUp;
	Ogre::Quaternion mOrient;
	float		mInitializeTime;
	Behavior*	mBehavior;
public:
	Trajectory(int _mNumTrajectory, Ogre::Vector3 _mPosition, Ogre::Vector3 _mDirection)
		:mNumTrajectory(_mNumTrajectory), mPosition(_mPosition), mDirection(_mDirection),
		mInitializeTime(0), mUp(Ogre::Vector3::UNIT_Z), mBehavior(0), mNeedUpdate(false)
	{}
	virtual ~Trajectory()
	{}
	virtual void AddBall(BallList& out)=0;
	virtual void AddBall(BallVector& out)=0;
	virtual BallList	GenerateBallList()=0;
	virtual BallVector	GenerateBallVector()=0;
	virtual BallVector& GetBallVector()=0;
	virtual void SetBehavior(Behavior* b) 
	{
		mBehavior = b;
		mNeedUpdate = true;
		CheckModify();
	}
protected:
	BallVector mBall_PreComptue;
	bool		mNeedUpdate;
	virtual void CheckModify()
	{
		if (mNeedUpdate)
			Modifyed();
	}
	virtual void Modifyed()=0;
};
SHARE_PTR(Trajectory)
