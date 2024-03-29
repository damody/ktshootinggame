#include "split.h"
#include "algo/sgmath.h"

int Split::UpdateBall( Ball* b, float elapsedtime )
{
	if(abs(mOAngle) < mMaxAngle)
	{
		b->mDirection = GetRotation(b->mDirection, mAngle *elapsedtime);
		mOAngle+=mAngle*elapsedtime;
	}
	b->mPosition += b->mDirection * mVelocity * elapsedtime;
	return Ball::FLY;
}
