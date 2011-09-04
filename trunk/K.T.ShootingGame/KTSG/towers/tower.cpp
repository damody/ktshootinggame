
#include "tower.h"
#include "global.h"
#include "bullets\bullet.h"

Texture_Sptr texture;
BulletVertex ball_pic;
Ball* GetBulletBall()
{
	//Bullet* bullet = Bullet::pool.construct(texture);
	Bullet* bullet = new Bullet(texture);
	bullet->m_pic = ball_pic;
	return static_cast<Ball*>(bullet);
}

BallptrVector Tower::Update(float dt)
{
	BallptrVector bv;
	m_elapsedTime += dt;
	m_Trajectory->Direction() = GetRotation(Ogre::Vector3::UNIT_X, m_angle);
	if (m_elapsedTime >= m_atkSpeed)
	{
		m_Trajectory->Position() = m_position;
		texture = m_ball_texture;
		ball_pic = m_ball_pic;
		bv = m_Trajectory->NewBallptrVector(GetBulletBall);
		m_elapsedTime = 0;
	}
	return bv;
}

