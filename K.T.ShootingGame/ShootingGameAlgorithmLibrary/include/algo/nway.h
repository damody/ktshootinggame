#pragma once
#include "Trajectory.h"
#include <iostream>
#include <algorithm>

class NWay : public Trajectory
{
public:
	float		mRadiationAngle;
	NWay(int _mNumTrajectory, Ogre::Vector3 _mPosition, Ogre::Vector3 _mDirection, float _angle = 90.0f)
		:Trajectory(_mNumTrajectory, _mPosition, _mDirection), mRadiationAngle(_angle)
	{}
	virtual ~NWay()
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
		float start = -mRadiationAngle*0.5f;
		if (mNumTrajectory > 1)
			step_angle = mRadiationAngle/(mNumTrajectory-1);
		else
			start = 0;
		for (int i = 0;i < mNumTrajectory;i++, start += step_angle)
		{
			Ball ball(mPosition, GetRotation(mDirection, start), mBehavior);
			ball.Update(mInitializeTime);
			mBall_PreComptue.push_back(ball);
		}
		mNeedUpdate = false;
	}
};
