#include "ball.h"
boost::object_pool<Ball> pool_Ball;

int Ball::Update( float elapsedtime )
{
	if (mpBehavior)
	{
		mpBehavior->UpdateBall(this, elapsedtime*mTimeRate);
		return FLY;
	}
	else
		return STOP;
}

bool Ball::HasBehavior()
{
	return mpBehavior!=NULL;
}

