#pragma once
#include <vector>
#include "Trajectory.h"

struct TrajectoryFrame
{
	TrajectoryFrame(Trajectory* _mBehavior, float _mStartTime)
		:mTrajectory(_mBehavior), mStartTime(_mStartTime)
	{}
	Trajectory* mTrajectory;
	float	mStartTime;
	bool operator < (const TrajectoryFrame& rhs) const
	{
		return mStartTime < rhs.mStartTime;
	}
	friend bool operator < (const TrajectoryFrame& lhs, const float rhs);
	friend bool operator < (const float lhs, const TrajectoryFrame& rhs);
};
bool operator < (const TrajectoryFrame& lhs, const float rhs) 
{
	return lhs.mStartTime < rhs;
}
bool operator < (const float lhs, const TrajectoryFrame& rhs) 
{
	return lhs < rhs.mStartTime;
}
typedef std::vector<TrajectoryFrame> TrajectoryFrames;
  
class TrajectoryAnimator
{
public:
	Ogre::Vector3	mPosition;
	Ogre::Vector3	mDirection;
	Ogre::Vector3	mUp;
	Ogre::Quaternion mOrient;
	TrajectoryFrames mBehaviorFrames;
	float		mOffsetTime;
	bool		mLoop;
	TrajectoryAnimator(float offsetTime = 0, bool loop = true)
		:mOffsetTime(offsetTime), mLoop(loop)
	{
	}
	void AddBehavior(Trajectory* b, float time);
	// if behavior no sort, it's error!
	void AddBehaviorFrame(TrajectoryFrame& b);
	void Sort();
	Trajectory* GetNowBehavior(float time);
};

