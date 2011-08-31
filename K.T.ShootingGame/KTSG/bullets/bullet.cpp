
#include "bullet.h"

boost::object_pool<Bullet> pool_Bullet;

void Bullet::UpdateDataToDraw()
{
	m_pic.size.x = 50;
	m_pic.size.y = 50;
	m_pic.position.x = mPosition.x;
	m_pic.position.y = mPosition.y;
	m_pic.position.z = mPosition.z;
	m_pic.angle = GetAngle(mDirection.x, mDirection.y).valueDegrees();
	m_pic.picpos.x = 1;
	m_pic.picpos.y = 1;
	m_pic.picpos.z = 4;
	m_pic.picpos.w = 2;
}

int Bullet::Update( float dt )
{
	int res = Ball::Update(dt);
	UpdateDataToDraw();
	return res;
}
