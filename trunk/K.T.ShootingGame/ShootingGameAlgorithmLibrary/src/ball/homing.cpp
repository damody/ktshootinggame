#include "homing.h"

int Homing::UpdateBall( Ball* b, float elapsedtime )
{
	HomingData* data = (HomingData*)b->mData;

	Ogre::Vector3 enemyPos = data->GetEnemyPos();

	Ogre::Vector3 direction = enemyPos - b->mPosition;

	if(direction.angleBetween(b->mDirection).valueDegrees() > 45)
		b->mDirection = direction;

	b->mPosition += b->mDirection * data->mVelocity * elapsedtime;
	return Ball::FLY;
}
