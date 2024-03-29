//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : PathInterpolater.h
//  @ Date : 2011/9/3
//  @ Author : 
//
//


#if !defined(_PATHINTERPOLATER_H)
#define _PATHINTERPOLATER_H
#include "math/OgreVector3.h"
#include <vector>
#include <algorithm>

struct PathPoint
{
	PathPoint(){}
	PathPoint(float _time, Ogre::Vector3 _pos)
		:time(_time), pos(_pos)
	{}
	float time;
	Ogre::Vector3 pos;
	bool operator < (const PathPoint&rhs)
	{
		return time < rhs.time;
	}
};
typedef std::vector<PathPoint> PathPoints;

class PathInterpolater
{
public:
	PathInterpolater():m_needsort(true){}
	Ogre::Vector3 m_position;
	void AddPoint(float time, Ogre::Vector3 p);
	virtual Ogre::Vector3 GetValue(float time)=0;
	void Clear();
	virtual ~PathInterpolater(){}
protected:
	void CheckSort();
	bool m_needsort;
	PathPoints m_points;
};

#endif  //_PATHINTERPOLATER_H
