#pragma once
#include "algo/sgmath.h"

Ogre::Vector3 GetRotation( const Ogre::Vector3& src, float angle, const Ogre::Vector3& middle_up )
{
	Ogre::Quaternion q;
	q.FromAngleAxis( Ogre::Degree(angle), middle_up );
	return q * src;
}

Ogre::Vector2 GetRotation( const Ogre::Vector2& src, float angle, const Ogre::Vector2& middle )
{
	Ogre::Quaternion q;
	Ogre::Vector3 tmpsrc(src.x, src.y, 0);
	Ogre::Vector3 up(middle.x, middle.y, -1);
	q.FromAngleAxis( Ogre::Degree(angle), up );
	tmpsrc = q * tmpsrc;
	return Ogre::Vector2(tmpsrc.x, tmpsrc.y);
}

Ogre::Degree GetAngle( float x, float y )
{
	return Ogre::Degree(Ogre::Radian(atan2f(x, y)));
}
