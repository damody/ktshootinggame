//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Polygon.h
//  @ Date : 2011/9/4
//  @ Author : damody
//  Reference: http://www.codeproject.com/KB/GDI-plus/PolygonCollision.aspx
//
//


#if !defined(_POLYGON2D_H)
#define _POLYGON2D_H
#include "math\OgreVector2.h"
#include "math\OgreVector3.h"
#include "algo\sgmath.h"
#include <vector>

typedef std::vector<Ogre::Vector2> Vector2s;
class Polygon2D 
{
public:
	Polygon2D(bool computeCentroid = false)
		:m_computeCentroid(computeCentroid), m_angle(0){}
	Vector2s& Points()
	{
		m_needBuildEdges = true;
		return m_points;
	}
	void AddPoint(float x, float y)
	{
		m_needBuildEdges = true;
		m_points.push_back(Ogre::Vector2(x, y));
	}
	void AddPoint(const Ogre::Vector2& p)
	{
		m_needBuildEdges = true;
		m_points.push_back(p);
	}
	void Offset(float x, float y)
	{
		for (Vector2s::iterator it = m_points.begin();
			it != m_points.end();++it)
		{
			it->x += x;
			it->y += y;
		}
	}
	void Offset(const Ogre::Vector2& v)
	{
		for (Vector2s::iterator it = m_points.begin();
			it != m_points.end();++it)
		{
			*it += v;
		}
	}
	void Offset(const Ogre::Vector3& v)
	{
		for (Vector2s::iterator it = m_points.begin();
			it != m_points.end();++it)
		{
			it->x += v.x;
			it->y += v.y;
		}
	}
	void SetAngle(float angle)
	{
		for (Vector2s::iterator it = m_points.begin();
			it != m_points.end();++it)
		{
			*it = GetRotation(*it, angle-m_angle, Ogre::Vector2::ZERO);
		}
		m_angle = angle;
	}
	void Rotation(float angle, const Ogre::Vector2& middle = Ogre::Vector2::ZERO)
	{
		m_angle = angle;
		for (Vector2s::iterator it = m_points.begin();
			it != m_points.end();++it)
		{
			*it = GetRotation(*it, angle, middle);
		}
	}
	bool IsCollision(const Polygon2D& rhs);
	void CheckBuildEdges();
	Ogre::Vector2 Centroid()
	{
		bool tmp = m_computeCentroid;
		m_computeCentroid = true;
		BuildEdges();
		m_computeCentroid = tmp;
		return m_centroid;
	}
private:
	void BuildEdges();
	// Calculate the distance between [minA, maxA] and [minB, maxB]
	// The distance will be negative if the intervals overlap
	inline float IntervalDistance(float minA, float maxA, float minB, float maxB)
	{
		if (minA < minB) {
			return minB - maxA;
		} else {
			return minA - maxB;
		}
	}
	// Calculate the projection of a polygon on an axis and returns it as a [min, max] interval
	void ProjectPolygon(const Ogre::Vector2& axis, const Polygon2D& polygon, float* min, float* max);
private:
	Vector2s m_points, m_edges;
	bool	m_computeCentroid; // true
	Ogre::Vector2 m_centroid;
	float	m_radius;
	bool	m_needBuildEdges;
	float	m_angle;
};

#endif  //_POLYGON_H