#include "gravity.h"

int Gravity::UpdateBall( Ball* b, float elapsedtime )
{
	mForce -= mGravity * elapsedtime;

	b->mDirection += mForce;

	b->mPosition += b->mDirection * mVelocity * elapsedtime;
	return Ball::FLY;
}
