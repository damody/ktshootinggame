#pragma once
#include "algo/sgmath.h"

Ogre::Vector3 GetRotation( const Ogre::Vector3& src, const Ogre::Vector3& up, float angle )
{
	Ogre::Quaternion q;
	q.FromAngleAxis( Ogre::Degree(angle), up );
	return q * src;
}

Ogre::Degree GetAngle( float x, float y )
{
	if (abs(y)<0.001)
		return Ogre::Degree(0);
	return Ogre::Degree(Ogre::Radian(atanf(x/y)));
}
