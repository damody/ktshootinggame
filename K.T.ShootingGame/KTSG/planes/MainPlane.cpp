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

#include "MainPlane.h"
#include "EnemyMainPlane.h"
#include "DX11/InputState.h"
#include "algo/sgmath.h"
#include "DX11/InitDirect3DApp.h"
#include "global.h"
#include "DX11/WaveSound.h"
#include <algo/nway.h>
#include <ball/homing.h>
#include <iostream>
#include <boost/bind.hpp>

Texture_Sptr texture2;
BulletVertex ball_pic2;
Ball* GetBulletBall2()
{
	//Bullet* bullet = Bullet::pool.construct(texture);
	Bullet* bullet = new Bullet(texture2);
	bullet->m_pic = ball_pic2;
	return static_cast<Ball*>(bullet);
}

void MainPlane::Update(float dt) 
{
	if(motherShip)
	{
		m_position = motherShip->m_position + GetRotation(motherShipOffset, motherShip->m_angle);
		m_angle = motherShip->m_angle;
		m_Polygon2D.SetAngle(m_angle);
	}
	else
	{
		Ogre::Vector3 temp = Ogre::Vector3::ZERO;
		if(InputStateS::instance().isKeyPress(KEY_UP))		temp.y = dt * 140;
		if(InputStateS::instance().isKeyPress(KEY_DOWN))	temp.y = -dt * 140;
		if(InputStateS::instance().isKeyPress(KEY_RIGHT))	m_angle += dt * 30;
		if(InputStateS::instance().isKeyPress(KEY_LEFT))	m_angle -= dt * 30;
		if(InputStateS::instance().isKeyDown(KEY_SPACE))
		{
			std::vector<EnemyMainPlane*> enemies = InitDirect3DApp::dxAppInstance->GetEnemies();
			EnemyMainPlane* enemyTemp = enemies.at(0);
			float distance = m_position.distance(enemyTemp->m_position);
			for(std::vector<EnemyMainPlane*>::iterator it = enemies.begin()+1;
				it != enemies.end();
				it++)
			{
				float distanceTemp = m_position.distance((*it)->m_position);
				if(distanceTemp < distance)
				{
					distance = distanceTemp;
					enemyTemp = *it;
				}
			}
			NWay* nWay = new NWay(1, m_position + GetRotation(Ogre::Vector3(0, 200, 0), m_angle), GetRotation(Ogre::Vector3(0, 1, 0), m_angle));
			nWay->mPolygon.AddPoint(0, 0);
			nWay->mPolygon.AddPoint(0, 20);
		
			Homing* homing = new Homing;
			homing->mVelocity = 50;
			homing->GetEnemyPos = boost::bind(&EnemyMainPlane::GetPos, enemyTemp);
			nWay->mBehavior = homing;
			nWay->SetRadiationAngle(180);
			
			texture2 = g_TextureManager.GetTexture(103);
			ball_pic2.picpos.x = 1;
			ball_pic2.picpos.y = 1;  
			ball_pic2.picpos.z = 2;
			ball_pic2.picpos.w = 2;
			ball_pic2.size.x = 2;
			ball_pic2.size.y = 20;
			BallptrVector bv = nWay->NewBallptrVector(GetBulletBall2);
			for(size_t i=0; i<bv.size(); i++)
			{
				bv[i]->mPolygon2D.Offset(bv[i]->mPosition);
			}
			g_BallptrManager.AddBallptrs(bv);
		}

		Ogre::Vector3 trans = GetRotation(temp, m_angle);
		m_position += trans;
		m_Polygon2D.SetAngle(m_angle);
	}

	static float startvalue = 0;
	startvalue += dt;
	UpdateTower(dt);
	UpdateDataToDraw();
}

int MainPlane::UpdateTower(float dt)
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

void MainPlane::UpdateDataToDraw()
{
	m_pic.position.x = m_position.x;
	m_pic.position.y = m_position.y;
	m_pic.position.z = 0;
	m_pic.angle = m_angle;
	m_pic.size.x = (float)m_w;
	m_pic.size.y = (float)m_h;
}

MainPlane::MainPlane()
{
	motherShip = NULL;
	m_Polygon2D.AddPoint(-200, 0);
	m_Polygon2D.AddPoint(0, -100);
	m_Polygon2D.AddPoint(0, 150);
	m_Polygon2D.AddPoint(200, 0);
}


