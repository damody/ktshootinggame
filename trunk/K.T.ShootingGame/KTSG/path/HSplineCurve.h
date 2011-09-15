//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : HSplineCurve.h
//  @ Date : 2011/9/3
//  @ Author : 
//
//


#if !defined(_HSPLINECURVE_H)
#define _HSPLINECURVE_H

#include "PathInterpolater.h"

class HsplineCurve : public PathInterpolater
{
public:
	Ogre::Vector3 GetValue(float time);
	static Ogre::Vector3 CalcHSplineCurvePos(const Ogre::Vector3& p4, const Ogre::Vector3& p3,
		const Ogre::Vector3& p2, const Ogre::Vector3& p1, float Scalar, float c = 0.4f)
	{
		float S2 = Scalar*Scalar, S3 = Scalar*Scalar*Scalar,tension = (1.0f-c)/2;
		Ogre::Vector3 start = p2, end = p3, cnt1 = (p1-p3)*tension, cnt2 = (p2-p4)*tension;
		Ogre::Vector3 out = (start * (-2.0f*S3 + 3.0f *S2) +
			end * (2.0f*S3 -  3.0f *S2 + 1) +
			cnt1 * (S3 - S2) +
			cnt2 * (S3 - 2*S2 + Scalar));
		return out;
	}
};

#endif  //_HSPLINECURVE_H