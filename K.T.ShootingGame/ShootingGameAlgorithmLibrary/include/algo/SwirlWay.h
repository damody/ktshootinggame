#pragma once
#include "Trajectory.h"
#include <iostream>
#include <algorithm>

class SwirlWay : public Trajectory
{
public:
	float mSecPerCircle;
	int mCircles;
	SwirlWay(int _mNumPerCircle, int _mCircles, float _mSecPerCircle, Ogre::Vector3 _mPosition)
		:Trajectory(_mNumPerCircle, _mPosition, Ogre::Vector3(0,0,0)), mSecPerCircle(_mSecPerCircle), mCircles(_mCircles)
	{}
	virtual ~SwirlWay()
	{}
	
protected:
	virtual void Modifyed();
};
