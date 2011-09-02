#include "straight.h"

int Straight::UpdateBall( Ball* b, float elapsedtime )
{
	b->mPosition += b->mDirection * mVelocity * elapsedtime;
	return Ball::FLY;
}

