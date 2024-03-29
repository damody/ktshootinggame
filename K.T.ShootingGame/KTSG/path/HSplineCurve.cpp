//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : HSplineCurve.cpp
//  @ Date : 2011/9/3
//  @ Author : 
//
//


#include "HSplineCurve.h"

Ogre::Vector3 HsplineCurve::GetValue(float time)
{
	CheckSort();
	if (m_points.empty())
		return Ogre::Vector3::ZERO;
	int index[4] = {0};
	const int size = (int)m_points.size();
	if (size == 1)
		return m_points[0].pos;
	else if (m_points[0].time > time)
		return m_points[0].pos;
	int i;
	if (m_points.back().time >= time)
	{
		for(i=0; i < size; i++) 
		{
			if (m_points[i].time > time)
			{
				time = (time - m_points[i-1].time)/(m_points[i].time-m_points[i-1].time);
				break;
			}
		}
	}
	else
	{
		i = size;
		time = time-m_points[i-1].time;
	}	
	index[0] = i-2;
	index[1] = i-1;
	index[2] = i;
	index[3] = i+1;
	for (int j = 0;j<4;++j)
	{
		if (index[j] < 0)
			index[j] = 0;
		if (index[j] >= size)
			index[j] = size-1;
	}
	Ogre::Vector3 out1 = CalcHSplineCurvePos(m_points[index[0]].pos,
		m_points[index[1]].pos,
		m_points[index[2]].pos,
		m_points[index[3]].pos,
		time);
	return out1+m_position;
}

