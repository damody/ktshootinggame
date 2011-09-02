#include "split.h"
#include "algo/sgmath.h"

int Split::UpdateBall( Ball* b, float elapsedtime )
{
	SplitData* data = (SplitData*)b->mData;

	if(abs(data->mOAngle) < data->mMaxAngle)
	{
		b->mDirection = GetRotation(b->mDirection, Ogre::Vector3::NEGATIVE_UNIT_Z, data->mAngle *elapsedtime);
		data->mOAngle+=data->mAngle*elapsedtime;
	}
	b->mPosition += b->mDirection * data->mVelocity * elapsedtime;
	return Ball::FLY;
}
