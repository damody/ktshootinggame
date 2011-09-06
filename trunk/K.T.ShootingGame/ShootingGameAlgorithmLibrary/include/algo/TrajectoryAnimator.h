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
bool operator < (const TrajectoryFrame& lhs, const float rhs);
bool operator < (const float lhs, const TrajectoryFrame& rhs);
typedef std::vector<TrajectoryFrame> TrajectoryFrames;
  
class TrajectoryAnimator
{
public:
	Ogre::Vector3	mPosition;
	Ogre::Vector3	mDirection;
	Ogre::Vector3	mUp;
	Ogre::Quaternion mOrient;
	TrajectoryFrames mBehaviorFrames;
	float		mElapsedTime;
	float		mStopTime;
	bool		mLoop;

	bool		mStarted;
	bool		mPaused;



	TrajectoryAnimator(float elapsedTime = 0, bool loop = true)
		:mElapsedTime(elapsedTime), mLoop(loop), mStopTime(0), mStarted(false), mPaused(false)
	{
	}
	void AddTrajectory(Trajectory* b, float time);
	// if behavior no sort, it's error!
	void AddTrajectoryFrame(TrajectoryFrame& b);
	void Sort();
	Trajectory* GetNowTrajectory(float time);

	void Update(float dt);
	void Start();
	void Stop();
	Trajectory* Pause(float stopTime = 0);
};

