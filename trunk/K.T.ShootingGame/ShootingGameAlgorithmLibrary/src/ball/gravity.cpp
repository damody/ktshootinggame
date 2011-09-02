#include "gravity.h"

int Gravity::UpdateBall( Ball* b, float elapsedtime )
{
	GravityData* data = (GravityData*)b->mData;

	data->mForce -= data->mGravity * elapsedtime;

	b->mPosition += b->mDirection * data->mVelocity * elapsedtime;
	b->mPosition += data->mForce;
	return Ball::FLY;
}
