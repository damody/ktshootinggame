//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LinearLine.cpp
//  @ Date : 2011/9/3
//  @ Author : 
//
//


#include "LinearLine.h"

Ogre::Vector3 LinearLine::GetValue(float time) 
{
	CheckSort();
	if (m_points.empty())
		return Ogre::Vector3::ZERO;
	int index[2] = {0};
	const int size = m_points.size();
	if (size == 1)
		return m_points[0].pos;
	else if (m_points[0].time > time)
		return m_points[0].pos;
	int i;
	for(i=0; i < size; i++) 
	{
		if (m_points[i].time > time)
		{
			time = (time - m_points[i-1].time)/(m_points[i].time - m_points[i-1].time);
			break;
		}
	}
	index[0] = i-1;
	index[1] = i;
	for (int j = 0;j<2;++j)
	{
		if (index[j] < 0)
			index[j] = 0;
		if (index[j] >= size)
			index[j] = size-1;
	}
	Ogre::Vector3 out1 = CalcStraightPos(m_points[index[0]].pos,
		m_points[index[1]].pos,
		time);
	return out1;
}
