#pragma once
#include "Trajectory.h"
#include <iostream>
#include <boost/random.hpp>

class RandomWay : public Trajectory
{
public:
	boost::mt19937  mRandom; 
	float		mRadiationAngle;
	RandomWay(int _mNumTrajectory, Ogre::Vector3 _mPosition, Ogre::Vector3 _mDirection, float _angle = 90.0f)
		:Trajectory(_mNumTrajectory, _mPosition, _mDirection), mRadiationAngle(_angle)
	{}
	virtual ~RandomWay()
	{}
	virtual void SetRadiationAngle(float angle)
	{
		mRadiationAngle = angle;
		this->Modifyed();
	}
	Ogre::Vector3 GetRotation(const Ogre::Vector3 src, float angle)
	{
		Ogre::Quaternion q;
		q.FromAngleAxis( Ogre::Degree(angle), mUp );
		return q * src;
	}
	virtual void AddBall(BallList& out)
	{
		std::copy(mBall_PreComptue.begin(), mBall_PreComptue.end(), out.end());
	}
	virtual void AddBall(BallVector& out)
	{
		std::copy(mBall_PreComptue.begin(), mBall_PreComptue.end(), out.end());
	}
	virtual BallList GenerateBallList()
	{
		return BallList(mBall_PreComptue.begin(), mBall_PreComptue.end());
	}
	virtual BallVector& GetBallVector()
	{
		return mBall_PreComptue;
	}
	virtual BallVector GenerateBallVector()
	{
		return mBall_PreComptue;
	}
protected:
	virtual void Modifyed()
	{
		mBall_PreComptue.clear();
		mBall_PreComptue.reserve(mNumTrajectory);
		float step_angle;
		boost::uniform_real<float> rng(-mRadiationAngle*0.5, mRadiationAngle*0.5);
		for (int i = 0;i < mNumTrajectory;i++)
		{
			Ball ball(mPosition, GetRotation(mDirection, rng(mRandom)), mBehavior);
			ball.Update(mInitializeTime);
			mBall_PreComptue.push_back(ball);
		}
		mNeedUpdate = false;
	}
};
