#include "BallptrManager.h"

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

void BallptrManager::SetNumThreads( int i )
{
	if (i<=0) i=1;
	if (i>SGA_MAX_THREADS) i=SGA_MAX_THREADS;
	mNumThreads = i;
	mOver = true;
	mThreadgroup.join_all();
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

void BallptrManager::MutiThreadUpdate( int i )
{
	for (;!mOver;) // 程式還沒結束
	{
		work_info& info = *mThreadsWork[i];
		if (!info.work_done) // 要工作了
		{
			LOCK l(info.m); //鎖
			size_t numwork = info.works.size();
			for (size_t nw=0;nw<numwork;nw++)
			{
				BallptrVector& bv = *(info.works[nw].bv);
				size_t bsize = bv.size();
				for (size_t i=info.works[nw].begin;i < info.works[nw].end;i++)
				{
					if (i < bv.size())
					{
						bv[i]->Update(info.time);
						if (bv[i]->mBallStatus == Ball::DESTORY)
						{
							mDeleteVector.push_back(bv[i]);
							mBallptrVector.erase(mBallptrVector.begin()+i);
							i--;
						}
					}
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
			LOCK l(mThreadsWork[i]->m); // 鎖住並清除工作
			mThreadsWork[i]->works.clear();
		}
		double step = mBallptrVector.size()/(double)mNumThreads;
		double now_step = 0;
		for (int i=0;i<mNumThreads;i++)
		{
			LOCK l(mThreadsWork[i]->m); //鎖住並更新
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
			if (mBallptrVector[i]->mBallStatus == Ball::DESTORY)
			{
				mDeleteVector.push_back(mBallptrVector[i]);
				mBallptrVector.erase(mBallptrVector.begin()+i);
				i--;
				bsize--;
			}
		}
	}
}

#else

void BallptrManager::Update( float time )
{
	size_t bsize = mBallptrVector.size();
	for (size_t i=0;i < bsize;i++)
	{
		mBallptrVector[i]->Update(time);
		if (mBallptrVector[i]->mBallStatus == Ball::DESTORY)
		{
			mDeleteVector.push_back(mBallptrVector[i]);
			mBallptrVector.erase(mBallptrVector.begin()+i);
			i--;
			bsize--;
		}
	}
}

#endif
