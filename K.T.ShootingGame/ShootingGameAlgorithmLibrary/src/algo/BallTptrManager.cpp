#include "BallTptrManager.h"

#if (SGA_USE_MUTITHREAD > 0)
BallptrManager::BallptrManager( int _mNumThreads /*= 1 */ ) :mNumThreads(_mNumThreads), mOver(false)
{
	memset(mThreadsWork, 0, sizeof(mThreadsWork));
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			mThreadsWork[i] = new work_info;
			mThreadgroup.create_thread(
				boost::bind(&BallptrManager::MutiThreadUpdate, boost::ref(*this), i));
		}
	}
}

BallptrManager::~BallptrManager()
{
	mOver = true;
	mThreadgroup.join_all();
	for (int i=0;i<SGA_MAX_THREADS;i++)
	{
		if (mThreadsWork[i])
			delete mThreadsWork[i];
	}
}

void BallptrManager::MutiThreadUpdate( int i )
{
	for (;!mOver;) // �{���٨S����
	{
		work_info& info = *mThreadsWork[i];
		if (!info.work_done) // �n�u�@�F
		{
			LOCK l(info.m); //��
			size_t numwork = info.works.size();
			for (size_t nw=0;nw<numwork;nw++)
			{
				BallptrVector& bv = *(info.works[nw].bv);
				size_t bsize = bv.size();
				for (size_t i=info.works[nw].begin;i < info.works[nw].end;i++)
				{
					bv[i]->Update(info.time);
				}
			}
			info.work_done = true;
		}
	}
}

void BallptrManager::Update( float time )
{
	if (mNumThreads>1)
	{
		for (int i=0;i<mNumThreads;i++)
		{
			LOCK l(mThreadsWork[i]->m); // ����òM���u�@
			mThreadsWork[i]->works.clear();
		}
		double step = mBallptrVector.size()/(double)mNumThreads;
		double now_step = 0;
		for (int i=0;i<mNumThreads;i++)
		{
			LOCK l(mThreadsWork[i]->m); //����ç�s
			if (mThreadsWork[i]->work_done)
			{
				if ((int)now_step == mBallptrVector.size())
					break;
				mThreadsWork[i]->work_done = false;
				mThreadsWork[i]->time = time;
				work w;
				w.bv = &mBallptrVector;
				w.begin = (int)now_step;
				now_step += step;
				if ((size_t)now_step >= mBallptrVector.size())
					now_step = mBallptrVector.size();
				w.end = (int)now_step;
				mThreadsWork[i]->works.push_back(w);
			}
		}
	}
	else
	{
		size_t bsize = mBallptrVector.size();
		for (size_t i=0;i < bsize;i++)
		{
			mBallptrVector[i]->Update(time);
		}
	}
}

#else

void BallptrManager::Update( float time )
{
	Trajectory_Sptrs::iterator it = mTrajectoryRawPtrs.begin();
	for (;it != mTrajectoryRawPtrs.end();it++)
	{
		BallTptrVector& bv = it->GetBallVector();
		size_t bsize = bv.size();
		for (size_t i=0;i < bsize;i++)
		{
			bv[i].Update(time);
		}
	}
}
#endif