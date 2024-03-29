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

#include "EnemyPlane.h"
#include "DX11/InputState.h"
#include "algo/sgmath.h"
#include "DX11/InitDirect3DApp.h"
#include "global.h"
#include "DX11/WaveSound.h"

void EnemyPlane::Update(float dt) 
{
	m_position = m_path->GetValue(m_elapsedTime);
	m_angle = GetAngle(m_position.x-m_lastpos.x, m_position.y-m_lastpos.y).valueDegrees();
	m_elapsedTime += dt;
	m_Polygon2D.SetAngle(m_angle);
	UpdateTower(dt);
	UpdateDataToDraw();
	m_lastpos = m_position;
}

int EnemyPlane::UpdateTower(float dt)
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
			g_EnemyBallptrManager.AddBallptrs(bv);
			WavSoundS::instance().PlayDup(18);
		}
	}
	return 0;
}

void EnemyPlane::UpdateDataToDraw()
{
	m_pic.position.x = m_position.x;
	m_pic.position.y = m_position.y;
	m_pic.position.z = 0;
	m_pic.angle = m_angle;
	m_pic.size.x = (float)m_w;
	m_pic.size.y = (float)m_h;
}

EnemyPlane::EnemyPlane() : m_elapsedTime(0), m_hp(1)
{
	m_Polygon2D.AddPoint(-60, 0);
	m_Polygon2D.AddPoint(0, -35);
	m_Polygon2D.AddPoint(0, 35);
	m_Polygon2D.AddPoint(60, 0);
}


