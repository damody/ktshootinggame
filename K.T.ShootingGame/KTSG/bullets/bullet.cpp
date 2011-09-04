
#include "bullet.h"

void Bullet::UpdateDataToDraw()
{
	m_pic.position.x = mPosition.x;
	m_pic.position.y = mPosition.y;
	m_pic.position.z = mPosition.z;
	m_pic.angle = GetAngle(mDirection.x, mDirection.y).valueDegrees();
}

int Bullet::Update( float dt )
{
	int res = Ball::Update(dt);
	UpdateDataToDraw();
	if (mPosition.x > 1920+300 || mPosition.x < -300)
		mBallStatus = Ball::DESTORY;
	if (mPosition.y > 1200+300 || mPosition.y < -300)
		mBallStatus = Ball::DESTORY;
	return res;
}

bool CompareBullet( const Ball* lhs, const Ball* rhs )
{
	return (*(Bullet*)lhs)<(*(Bullet*)rhs);
}
