#pragma once
#include "common/SGA_config.h"
#include "common/shared_ptr.h"
#include "ball/ballTptr.h"
#include "Trajectory.h"

class BallptrManager
{
public:
	BallptrVector	mBallptrVector;
private:
	int		mNumThreads;
#if (SGA_USE_MUTITHREAD > 0)
	boost::thread_group mThreadgroup;
	struct work
	{
		BallptrVector* bv;
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
#if (SGA_USE_MUTITHREAD > 0)
	BallptrManager( int _mNumThreads = 1 );
	~BallptrManager();
	void MutiThreadUpdate( int i );
	void Update( float time );
#else
	BallptrManager(int _mNumThreads=1)
		:mNumThreads(_mNumThreads)
	{}
	void Update( float time );
#endif
	void SetNumThreads( int i )
	{
		if (i<=0) i=1;
		if (i>SGA_MAX_THREADS) i=SGA_MAX_THREADS;
	}
	void AddBallptr( Ball* b )
	{
		mBallptrVector.push_back(b);
	}
	void AddBallptrs( const BallptrVector& bv )
	{
		for (BallptrVector::const_iterator it = bv.begin();
			it != bv.end(); ++it)
		{
			mBallptrVector.push_back(*it);
		}
	}
};
