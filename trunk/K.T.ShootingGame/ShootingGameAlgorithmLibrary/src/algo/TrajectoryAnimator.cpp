#include "TrajectoryAnimator.h"
#include <algorithm>

void TrajectoryAnimator::AddBehavior( Trajectory* b, float time )
{
	mBehaviorFrames.push_back(TrajectoryFrame(b, time));
}

void TrajectoryAnimator::AddBehaviorFrame( TrajectoryFrame& b )
{
	mBehaviorFrames.push_back(b);
}

void TrajectoryAnimator::Sort()
{
	sort(mBehaviorFrames.begin(), mBehaviorFrames.end());
}

Trajectory* TrajectoryAnimator::GetNowBehavior( float time )
{
	return lower_bound(mBehaviorFrames.begin(), mBehaviorFrames.end(), time)->mTrajectory;
}

void TrajectoryAnimator::Start()
{
	mStarted = true;
	mPaused = false;
}

void TrajectoryAnimator::Stop()
{
	mStarted = false;
	mPaused = false;
	mElapsedTime = 0;
}

Trajectory* TrajectoryAnimator::Pause(float stopTime)
{
	mPaused = true;
	mStopTime = stopTime;

	return GetNowTrajectory(mElapsedTime);
}

void TrajectoryAnimator::Update(float dt)
{
	if(!mPaused && mStarted)
	{
		mElapsedTime += dt;
	}
	else if(mPaused && mStopTime > 0)
	{
		mStopTime -= dt;

		if(mStopTime < 0)
		{
			mStopTime = 0;
			mPaused = false;
		}
	}
}
