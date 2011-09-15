//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LoadStage.cpp
//  @ Date : 2011/9/6
//  @ Author : 
//
//


#include "LoadStage.h"
#include "global.h"

void LoadStage::LoadNewStage( std::string path, Stage& toStage )
{
	m_Lua.InputLuaFile(path.c_str());
	for (int i=1;;++i)
	{
		if (!m_Lua.CheckNotNil("stage/%d/time", i))
			break;
		float time = (float)m_Lua.getLua<double>("stage/%d/time", i);
		EnemyPlane* eplane = new EnemyPlane;
		eplane->m_angle = 0;
		eplane->m_w = m_Lua.getLua<int>("stage/%d/plane/w", i);
		eplane->m_h = m_Lua.getLua<int>("stage/%d/plane/h", i);
		Polygon2D poly;
		for (int k=1;;++k)
		{
			if (!m_Lua.CheckNotNil("stage/%d/plane/polygon/%d/x", i, k))
				break;
			float x = (float)m_Lua.getLua<double>("stage/%d/plane/polygon/%d/x", i, k);
			float y = (float)m_Lua.getLua<double>("stage/%d/plane/polygon/%d/y", i, k);
			poly.AddPoint(x, y);
		}
		eplane->m_Polygon2D=poly;
		PathInterpolater* pathInter;
		int pathtype = PathFactory::Generate(m_Lua.getLua<const char*>("stage/%d/plane/path/type", i), pathInter);
		pathInter->m_position.x = (float)m_Lua.getLua<double>("stage/%d/plane/path/offset/x", i);
		pathInter->m_position.y = (float)m_Lua.getLua<double>("stage/%d/plane/path/offset/y", i);
		for (int j=1;;++j)
		{
			if (!m_Lua.CheckNotNil("stage/%d/plane/path/%d/time", i, j))
				break;
			pathInter->AddPoint((float)m_Lua.getLua<double>("stage/%d/plane/path/%d/time", i, j),
				Ogre::Vector3(
					(float)m_Lua.getLua<double>("stage/%d/plane/path/%d/x", i, j),
					(float)m_Lua.getLua<double>("stage/%d/plane/path/%d/y", i, j), 
					0)
				);
		}
		eplane->m_path = pathInter;
		Towers& towers=eplane->m_Towers;
		Trajectory* tjy;
		Behavior* bvr;
		poly.Clear();
		for (int j=1;;++j)
		{
			if (!m_Lua.CheckNotNil("stage/%d/plane/tower/%d/x", i, j))
				break;
			Tower tower;
			tower.m_ball_pic.picpos.x = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/picpos/x", i, j);
			tower.m_ball_pic.picpos.y = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/picpos/y", i, j);
			tower.m_ball_pic.picpos.z = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/picpos/w", i, j);
			tower.m_ball_pic.picpos.w = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/picpos/h", i, j);
			tower.m_ball_pic.size.x = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/ballw", i, j);
			tower.m_ball_pic.size.y = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/ballh", i, j);
			tower.m_ball_pic.angle = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/angle", i, j);
			tower.m_position.x = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/x", i, j);
			tower.m_position.y = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/y", i, j);
			tower.m_atk = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/atk", i, j);
			tower.m_atkSpeed = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/atkspeed", i, j);
			tower.m_ball_texture = g_TextureManager.GetTexture(m_Lua.getLua<int>("stage/%d/plane/tower/%d/ballpic", i, j));
			int tjytype = TrajectoryFactory::Generate(
				m_Lua.getLua<const char*>("stage/%d/plane/tower/%d/trajectory/type", i, j), tjy);
			tjy->mNumTrajectory = m_Lua.getLua<int>("stage/%d/plane/tower/%d/trajectory/num", i, j);
			switch (tjytype)
			{
			case TrajectoryFactory::NWAY:
				((NWay*)tjy)->SetRadiationAngle((float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/trajectory/RadiationAngle", i, j));
				break;
			case TrajectoryFactory::RANDOM_WAY:
				((RandomWay*)tjy)->SetRadiationAngle((float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/trajectory/RadiationAngle", i, j));
				break;
			case TrajectoryFactory::STRAIGHT_WAY:
				break;
			case TrajectoryFactory::SWIR_WAY:
				break;
			}
			tower.m_Trajectory = tjy;
			int bvrtype = BehaviorFactory::Generate(
				m_Lua.getLua<const char*>("stage/%d/plane/tower/%d/behavior/type", i, j), bvr);
			for (int k=1;;++k)
			{
				if (m_Lua.CheckNotNil("stage/%d/plane/tower/%d/behavior/polygon/%d/x", i, j, k))
				{
					float x = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/behavior/polygon/%d/x", i, j, k);
					float y = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/behavior/polygon/%d/y", i, j, k);
					poly.AddPoint(x, y);
				}
				else
					break;
			}
			tjy->mPolygon = poly;
			switch (bvrtype)
			{
			case BehaviorFactory::STRAIGHT:
				((Straight*)bvr)->mVelocity = (float)m_Lua.getLua<double>("stage/%d/plane/tower/%d/behavior/velocity", i, j);
				break;
			case BehaviorFactory::GRAVITY:
				break;
			case BehaviorFactory::HOMING:
				break;
			case BehaviorFactory::SPLIT:
				break;
			}
			tower.m_Behavior = bvr;
			tjy->SetBehavior(bvr);
			towers.push_back(tower);
		}
		toStage.AddEnmyPlane(time, eplane);
	}
	
}