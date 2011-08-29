#pragma once
#include "math\OgreVector3.h"
#include <cmath>

Ogre::Vector3 GetRotation(const Ogre::Vector3& src, const Ogre::Vector3& up, float angle);

Ogre::Degree GetAngle(float x, float y);
