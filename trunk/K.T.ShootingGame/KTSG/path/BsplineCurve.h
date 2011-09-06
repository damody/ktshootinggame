//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : BsplineCurve.h
//  @ Date : 2011/9/3
//  @ Author : 
//
//


#if !defined(_BSPLINECURVE_H)
#define _BSPLINECURVE_H

#include "PathInterpolater.h"

class BsplineCurve : public PathInterpolater
{
public:
	Ogre::Vector3 GetValue(float time);
	static Ogre::Vector3 CalcBSplineCurvePos(const Ogre::Vector3& start, const Ogre::Vector3& cnt1,
		const Ogre::Vector3& cnt2, const Ogre::Vector3& end, float Scalar)
	{
		float S2 = Scalar*Scalar, S3 = Scalar*Scalar*Scalar;
		Ogre::Vector3 out = (start * (1.0f + 3.0f *(S2 - Scalar) - S3) +
			cnt1 * (4.0f - 6.0f *S2 + 3.0f *S3) +
			cnt2 * (1.0f + 3.0f * (Scalar + S2 - S3)) +
			end * S3)/6.0f;
		return out;
	}
};

#endif  //_BSPLINECURVE_H