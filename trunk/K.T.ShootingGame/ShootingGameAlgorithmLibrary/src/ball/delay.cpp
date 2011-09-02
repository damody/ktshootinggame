#include "delay.h"

int Delay::UpdateBall( Ball* b, float elapsedtime )
{
	DelayData* data = (DelayData*)b->mData;


	if(data->mElapsedTime >= data->mLaunchTime)
		b->mPosition += b->mDirection * data->mVelocity * elapsedtime;
	else
		data->mElapsedTime += elapsedtime;
	return Ball::FLY;
}
