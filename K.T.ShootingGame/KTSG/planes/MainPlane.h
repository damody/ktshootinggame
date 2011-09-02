//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : MainPlane.h
//  @ Date : 2011/8/30
//  @ Author : 
//
//


#if !defined(_MAINPLANE_H)
#define _MAINPLANE_H

#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "math\OgreVector3.h"
#include "algo\nway.h"
#include "ball\straight.h"


class MainPlane {
public:
	DXVertex	m_pic;
	Texture_Sptr	m_texture;
	Ogre::Vector3	m_position;
	float		m_angle;
	int		m_hp;
	int		m_w, m_h;
	Trajectory*	m_nWay;
	Straight*	m_straight;

	MainPlane(Trajectory* nWay, Straight* straight):m_nWay(nWay), m_straight(straight)
	{

	}

	void Update(float dt);
	int  UpdateTower();
private:
	void UpdateDataToDraw();
};

#endif  //_MAINPLANE_H