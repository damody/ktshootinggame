#pragma once
#include "common/SGA_config.h"
#include "common/shared_ptr.h"
#include "Trajectory.h"
#include "ball/Polygon2D.h"
#include <ANN/ANN.h>
SHARE_PTR(ANNkd_tree)

class BallptrManager
{
public:
	BallptrVector	mBallptrVector;
	BallptrVector	mDeleteVector;
	ANNkd_tree_Sptr mkdTree;
private:
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
	ANNpointArray	dataPts;
	std::vector<int> ids;
	std::vector<float> dists;
public:
	BallptrManager( int _mNumThreads = 1 );
	~BallptrManager();
	void MutiThreadUpdate( int i );
	void Update( float time );
	void SetNumThreads( int i );
	void BuildKdtree();
	BallptrVector GetCollision( Polygon2D& poly, int collisionMask = 0xffffffff);
	void AddBallptr( Ball* b )
	{
		assert(!b->mPolygon2D.Points().empty());
		mBallptrVector.push_back(b);
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
