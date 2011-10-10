#pragma once
#include "math\OgreVector2.h"
#include "math\Polygon2D.h"

class AABB2D
{
public:
	AABB2D(const Polygon2D& poly)
	{
		m_min = m_max = poly.const_Points().front();
		for (size_t i = 1; i < poly.const_Points().size(); i++) 
			AddPoint(poly.const_Points()[i]);
	}
	void AddPoint(const Ogre::Vector2& p);
	AABB2D(){}
	AABB2D(const Ogre::Vector2& orgin)
		:m_min(orgin), m_max(orgin)
	{}
	void Big(float val)
	{
		m_min.x -= val;
		m_min.y -= val;
		m_max.x += val;
		m_max.y += val;
	}
	Ogre::Vector2 m_min, m_max;
};
