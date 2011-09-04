#pragma once
#include "Trajectory.h"
#include <iostream>
#include <algorithm>

class NWay : public Trajectory
{
public:
	float	mRadiationAngle;
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
	
protected:
	virtual void Modifyed();
};
