#include "homing.h"

int Homing::UpdateBall( Ball* b, float elapsedtime )
{
	Ogre::Vector3 enemyPos = GetEnemyPos();
	Ogre::Vector3 direction = enemyPos - b->mPosition;
	direction.normalise();
	//if(direction.angleBetween(b->mDirection).valueDegrees() < 45)
		b->mDirection = direction;
	b->mPosition += b->mDirection * mVelocity * elapsedtime;

	b->mPolygon2D.Offset(b->mDirection * mVelocity * elapsedtime);
	return Ball::FLY;
}
