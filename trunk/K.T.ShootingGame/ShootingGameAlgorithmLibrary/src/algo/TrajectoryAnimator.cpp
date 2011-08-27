#include "TrajectoryAnimator.h"
#include <algorithm>

void TrajectoryAnimator::AddBehavior( Trajectory* b, float time )
{
	mBehaviorFrames.push_back(TrajectoryFrame(b, time));
}

void TrajectoryAnimator::AddBehaviorFrame( TrajectoryFrame b )
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
