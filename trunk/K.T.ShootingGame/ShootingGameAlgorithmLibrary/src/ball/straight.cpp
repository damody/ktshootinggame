#include "straight.h"

int Straight::UpdateBall( Ball* b, float elapsedtime )
{
	StraightData* data = (StraightData*)b->mData;
	b->mPosition += b->mDirection * data->mVelocity * elapsedtime;
	return Ball::FLY;
}
