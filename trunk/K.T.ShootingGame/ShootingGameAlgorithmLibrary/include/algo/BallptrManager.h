#pragma once
#include "common/SGA_config.h"
#include "common/shared_ptr.h"
#include "Trajectory.h"
#include "ball/Polygon2D.h"

class BallptrManager
{
public:
	BallptrVector	mDeleteVector;
private:
	BallptrVector	mBallptrVector;
	struct axis_bind
	{
		axis_bind(float* v, Ball* b):
		val(v), ball(b){}
		float* val;
		Ball* ball;
		bool operator < (const axis_bind& ab)
		{
			return *val < *ab.val;
		}
	};
	typedef std::vector<axis_bind> axis_binds;
	int		mNumThreads;
	bool		mKdtreeBuild;
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
	axis_binds mXbinds, mYbinds;
public:
	BallptrManager( int _mNumThreads = 1 );
	~BallptrManager();
	bool Empty();
	const BallptrVector& Ballptrs();
	void MutiThreadUpdate( int i );
	void Update( float time );
	void SetNumThreads( int i );
	typedef bool (*CompareBall)(const Ball* lhs, const Ball* rhs);
	void Sort(CompareBall fun_cb);
	BallptrVector GetCollision( Polygon2D& poly, int collisionMask = 0xffffffff);
	void SortCollision()
	{
		std::sort(mXbinds.begin(), mXbinds.end());
		std::sort(mYbinds.begin(), mYbinds.end());
	}
	void AddBallptr( Ball* b )
	{
		assert(!b->mPolygon2D.Points().empty());
		mBallptrVector.push_back(b);
		mXbinds.push_back(axis_bind(&(mBallptrVector.back()->mPosition.x), mBallptrVector.back()));
		mYbinds.push_back(axis_bind(&(mBallptrVector.back()->mPosition.y), mBallptrVector.back()));
	}
	void AddBallptrs( const BallptrVector& bv )
	{
		for (BallptrVector::const_iterator it = bv.begin();
			it != bv.end(); ++it)
		{
			assert(!(*it)->mPolygon2D.Points().empty());
			mBallptrVector.push_back(*it);
		}
	}
};
