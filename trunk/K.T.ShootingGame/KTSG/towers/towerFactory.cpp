#include "towerFactory.h"
#include "../global.h"
#include "algo/nway.h"
#include "algo/RandomWay.h"
#include "ball/straight.h"


towerFactory::towerFactory()
{
}

Tower towerFactory::NewTower( Tower::tower_type type )
{
	int tp = (int)type;
	Tower t;
	t = m_TowerSet[tp-1];
	Straight* st = new Straight;
	Straight* oldst = dynamic_cast<Straight*>(t.m_Behavior);
	st->mVelocity = oldst->mVelocity;
	t.m_Behavior = st;
	t.m_Trajectory = new NWay(1, Ogre::Vector3(0,0,0), Ogre::Vector3(0,1,0));
	t.m_Trajectory->SetBehavior(t.m_Behavior);
	t.m_Trajectory->mPolygon.AddPoint(0,0);
	t.m_Trajectory->mPolygon.AddPoint(0,20);
	return t;
}

void towerFactory::TowerLvUp( Tower& tower )
{
	for (int i=0; i<m_TowerTypeNum; i++)
	{
		if (tower.m_type==m_TowerSet[i].m_type)
		{
			tower.m_level++;
			tower.m_hp+=m_TowerGrowTable[i].Hp;
			tower.m_atk+=m_TowerGrowTable[i].Atk;
			tower.m_atkSpeed+=m_TowerGrowTable[i].AtkSpeed;
			tower.m_rotateSpeed+=m_TowerGrowTable[i].RotateSpeed;
			return;
		}
	}
}

void towerFactory::Init()
{
	Tower nt;
	TowerGrowUp ntgu;
	char s[64];
	m_LuaCell.InputLuaFile("tower.lua");
	m_TowerTypeNum = m_LuaCell.getLua<int>("Towers/typenum");

	Straight* st;
	nt.m_level=1;

	for (int i=1; i<=m_TowerTypeNum; i++)
	{
		nt.m_texture = g_TextureManager.GetTexture(m_LuaCell.getLua<int>("Towers/tower%d/pic", i));
		nt.m_type = (Tower::tower_type)m_LuaCell.getLua<int>("Towers/tower%d/type", i);
		nt.m_hp = m_LuaCell.getLua<int>("Towers/tower%d/hp", i);
		nt.m_maxhp = nt.m_hp;
		nt.m_atk = (float)m_LuaCell.getLua<double>("Towers/tower%d/atk", i);
		nt.m_atkSpeed = (float)m_LuaCell.getLua<double>("Towers/tower%d/atkspeed", i);
		nt.m_atkSpeed = (float)m_LuaCell.getLua<double>("Towers/tower%d/atkspeed", i);
		nt.m_rotateSpeed = (float)m_LuaCell.getLua<double>("Towers/tower%d/RotateSpeed", i);
		nt.m_ball_texture = g_TextureManager.GetTexture(m_LuaCell.getLua<int>("Towers/tower%d/ballpic", i));
		st = new Straight;
		st->mVelocity = m_LuaCell.getLua<int>("Towers/tower%d/ballspeed", i);
		nt.m_Behavior = st;
		nt.m_Trajectory = new NWay(1, Ogre::Vector3(0,0,0), Ogre::Vector3(0,1,0));
		nt.m_Trajectory->SetBehavior(nt.m_Behavior);
		nt.m_Trajectory->mPolygon.AddPoint(0,0);
		nt.m_Trajectory->mPolygon.AddPoint(0,20);
		nt.m_ball_pic.picpos.x = (float)m_LuaCell.getLua<double>("Towers/tower%d/picpos/x", i);
		nt.m_ball_pic.picpos.y = (float)m_LuaCell.getLua<double>("Towers/tower%d/picpos/x", i);
		nt.m_ball_pic.picpos.z = (float)m_LuaCell.getLua<double>("Towers/tower%d/picpos/y", i);
		nt.m_ball_pic.picpos.w = (float)m_LuaCell.getLua<double>("Towers/tower%d/picpos/z", i);
		nt.m_ball_pic.size.x = (float)m_LuaCell.getLua<double>("Towers/tower%d/size/x", i);
		nt.m_ball_pic.size.y = (float)m_LuaCell.getLua<double>("Towers/tower%d/size/y", i);
		ntgu.Hp = m_LuaCell.getLua<int>("TowerLvUp/tower%d/hp", i);
		ntgu.Atk = (float)m_LuaCell.getLua<double>("TowerLvUp/tower%d/atk", i);
		ntgu.AtkSpeed = (float)m_LuaCell.getLua<double>("TowerLvUp/tower%d/atksp", i);
		ntgu.RotateSpeed = (float)m_LuaCell.getLua<double>("TowerLvUp/tower%d/rotatespeed", i);

		m_TowerSet.push_back(nt);
		m_TowerGrowTable.push_back(ntgu);
	}
}
