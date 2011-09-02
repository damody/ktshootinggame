#pragma once
#include "algo/RandomWay.h"
#include "algo/sgmath.h"
#include "ball/straight.h"

void RandomWay::Modifyed()
{
	mBall_PreComptue.clear();
	mBall_PreComptue.reserve(mNumTrajectory);
	boost::uniform_real<float> rng(-mRadiationAngle*0.5f, mRadiationAngle*0.5f);
	for (int i = 0;i < mNumTrajectory;i++)
	{
		Ball ball(mPosition, GetRotation(mDirection, mUp, rng(mRandom)), 0, mBehavior);
		((StraightData*)(ball.mData))->mVelocity = 50;
		ball.Update(mInitializeTime);
		mBall_PreComptue.push_back(ball);
	}
	mNeedUpdate = false;
}