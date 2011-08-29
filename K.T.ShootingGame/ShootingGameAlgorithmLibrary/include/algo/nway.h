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
	virtual void Modifyed();
};
