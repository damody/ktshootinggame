#pragma once
#include "StraightWay.h"
#include "algo/sgmath.h"
#include "ball/split.h"

void StraightWay::Modifyed()
{
	mBall_PreComptue.clear();
	mBall_PreComptue.reserve(mNumTrajectory);
	float step_angle = 0;
	float start = -mRadiationAngle*0.5f;
	if (mNumTrajectory > 1)
		step_angle = mRadiationAngle/(mNumTrajectory-1);
	else
		start = 0;
	for (int i = 0;i < mNumTrajectory;i++, start += step_angle)
	{
		Split* split = new Split;
		split->mAngle = start / mRadiationAngle*200;
		split->mVelocity = 500;
		split->mMaxAngle = mRadiationAngle*0.5f;
		split->mOAngle = 0;
		Ball ball(mPosition, mDirection, split);
		mBall_PreComptue.push_back(ball);
	}
	mNeedUpdate = false;
}
