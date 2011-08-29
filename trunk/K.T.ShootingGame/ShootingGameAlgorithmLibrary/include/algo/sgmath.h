#pragma once
#include "math\OgreVector3.h"

Ogre::Vector3 GetRotation(const Ogre::Vector3& src, const Ogre::Vector3& up, float angle)
{
	Ogre::Quaternion q;
	q.FromAngleAxis( Ogre::Degree(angle), up );
	return q * src;
}
