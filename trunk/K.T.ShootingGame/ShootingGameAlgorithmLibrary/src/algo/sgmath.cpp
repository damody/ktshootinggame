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
	return Ogre::Degree(Ogre::Radian(atan2f(x, y)));
}
