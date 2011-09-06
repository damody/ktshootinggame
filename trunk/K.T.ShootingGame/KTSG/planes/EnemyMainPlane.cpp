//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : MainPlane.cpp
//  @ Date : 2011/8/30
//  @ Author : 
//
//

#include "EnemyMainPlane.h"
#include "DX11/InputState.h"
#include "algo/sgmath.h"
#include "DX11/InitDirect3DApp.h"
#include "global.h"
#include "DX11/WaveSound.h"

void EnemyMainPlane::Update(float dt) 
{
// 	Ogre::Vector3 trans = GetRotation(Ogre::Vector3(0, dt*10, 0), m_angle);
// 	m_position += trans;

	m_position = m_path.GetValue(m_elapsedTime);
	
	/*if(m_elapsedTime - UINT(m_elapsedTime) > 0.9)*/
		//m_path.AddPoint(0.5f, Ogre::Vector3(rand() % 1440 + 0.0f, rand() % 900 + 0.0f, 0));

	m_elapsedTime += dt;

	m_Polygon2D.SetAngle(m_angle);

	UpdateTower(dt);
	UpdateDataToDraw();
}

int EnemyMainPlane::UpdateTower(float dt)
{
	for (Towers::iterator it = m_Towers.begin();
		it != m_Towers.end();++it)
	{
		it->m_angle = m_angle-90;
		BallptrVector bv = it->Update(dt);
		if (!bv.empty())
		{
			for (BallptrVector::iterator bvit = bv.begin();
				bvit != bv.end(); ++bvit)
			{
				(**bvit).mPosition = GetRotation((**bvit).mPosition, m_angle);
				(**bvit).mPosition += m_position;
				size_t size = (**bvit).mPolygon2D.Points().size();
				(**bvit).mPolygon2D.Offset((**bvit).mPosition);
			}
			g_BallptrManager.AddBallptrs(bv);
			WavSoundS::instance().PlayDup(18);
		}
	}
	return 0;
}

void EnemyMainPlane::UpdateDataToDraw()
{
	m_pic.position.x = m_position.x;
	m_pic.position.y = m_position.y;
	m_pic.position.z = 0;
	m_pic.angle = m_angle;
	m_pic.size.x = (float)m_w;
	m_pic.size.y = (float)m_h;
}

EnemyMainPlane::EnemyMainPlane() : m_elapsedTime(0)
{
	m_Polygon2D.AddPoint(-60, 0);
	m_Polygon2D.AddPoint(0, -35);
	m_Polygon2D.AddPoint(0, 35);
	m_Polygon2D.AddPoint(60, 0);
}


