#pragma once
#include "common/SGA_config.h"
#include "ball/ball.h"
#include "Trajectory.h"
#include "common/shared_ptr.h"

#ifdef SGA_USE_MUTITHREAD
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
typedef boost::mutex MUTEX;
typedef MUTEX::scoped_lock LOCK;
#endif

class BallManager
{
private:
	int		mNumThreads;
	BallVector	mBallVector;
	TrajectoryRawPtrs mTrajectoryRawPtrs;
#ifdef SGA_USE_MUTITHREAD
	boost::thread_group mThreadgroup;
	struct work
	{
		BallVector* bv;
		size_t	begin;
		size_t	end;
	};
	struct work_info
	{
		work_info():work_done(true)
		{}
		MUTEX	m;
		std::vector<work> works;
		float	time;
		bool	work_done;
	};
	SHARE_PTR(work_info)
	work_info* mThreadsWork[SGA_MAX_THREADS];
	bool mOver;
#endif	
public:
#ifdef SGA_USE_MUTITHREAD
	BallManager(int _mNumThreads=1);
	~BallManager();
#else
	BallManager(int _mNumThreads=1)
		:mNumThreads(_mNumThreads)
	{
	}
#endif
	void SetNumThreads(int i);
	void AddTrajectory(Trajectory* t);
	void Update(float time);
#ifdef SGA_USE_MUTITHREAD
	void MutiThreadUpdate(int i);
#endif
};
