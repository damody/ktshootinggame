#pragma once
#include "math\OgreVector2.h"
#include "math\OgreVector3.h"
#include <cmath>

Ogre::Vector3 GetRotation( const Ogre::Vector3& src, float angle, const Ogre::Vector3& middle_up = Ogre::Vector3::NEGATIVE_UNIT_Z );
Ogre::Vector2 GetRotation( const Ogre::Vector2& src, float angle, const Ogre::Vector2& middle = Ogre::Vector2::ZERO);
Ogre::Degree GetAngle(float x, float y);
