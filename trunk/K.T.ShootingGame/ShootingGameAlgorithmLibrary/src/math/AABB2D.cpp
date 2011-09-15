#include "AABB2D.h"

void AABB2D::AddPoint( const Ogre::Vector2& p )
{
	if (p.x > m_max.x)
		m_max.x = p.x;
	else if (p.x < m_min.x)
		m_min.x = p.x;
	if (p.y > m_max.y)
		m_max.y = p.y;
	else if (p.y < m_min.y)
		m_min.y = p.y;
}
