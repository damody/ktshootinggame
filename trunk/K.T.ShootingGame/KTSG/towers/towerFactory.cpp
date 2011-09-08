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
		sprintf_s(s, 64, "Towers/tower%d/pic", i);
		nt.m_texture = g_TextureManager.GetTexture(m_LuaCell.getLua<int>(s));

		sprintf_s(s, 64, "Towers/tower%d/type", i);
		nt.m_type = (Tower::tower_type)m_LuaCell.getLua<int>(s);

		sprintf_s(s, 64, "Towers/tower%d/type", i);
		nt.m_hp = (Tower::tower_type)m_LuaCell.getLua<int>("Towers/tower%d/type", i);
		nt.m_maxhp = nt.m_hp;

		sprintf_s(s, 64, "Towers/tower%d/atk", i);
		nt.m_atk = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/atkspeed", i);
		nt.m_atkSpeed = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/atkspeed", i);
		nt.m_atkSpeed = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/RotateSpeed", i);
		nt.m_rotateSpeed = m_LuaCell.getLua<double>(s);

		nt.m_ball_texture = g_TextureManager.GetTexture(m_LuaCell.getLua<int>("Towers/tower%d/ballpic", i));

		st = new Straight;
		sprintf_s(s, 64, "Towers/tower%d/ballspeed", i);
		st->mVelocity = m_LuaCell.getLua<int>(s);
		nt.m_Behavior = st;
		nt.m_Trajectory = new NWay(1, Ogre::Vector3(0,0,0), Ogre::Vector3(0,1,0));
		nt.m_Trajectory->SetBehavior(nt.m_Behavior);
		nt.m_Trajectory->mPolygon.AddPoint(0,0);
		nt.m_Trajectory->mPolygon.AddPoint(0,20);

		sprintf_s(s, 64, "Towers/tower%d/picpos/x", i);
		nt.m_ball_pic.picpos.x = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/picpos/x", i);
		nt.m_ball_pic.picpos.y = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/picpos/y", i);
		nt.m_ball_pic.picpos.z = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/picpos/z", i);
		nt.m_ball_pic.picpos.w = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/size/x", i);
		nt.m_ball_pic.size.x = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "Towers/tower%d/size/y", i);
		nt.m_ball_pic.size.y = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "TowerLvUp/tower%d/hp", i);
		ntgu.Hp = m_LuaCell.getLua<int>(s);

		sprintf_s(s, 64, "TowerLvUp/tower%d/atk", i);
		ntgu.Atk = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "TowerLvUp/tower%d/atksp", i);
		ntgu.AtkSpeed = m_LuaCell.getLua<double>(s);

		sprintf_s(s, 64, "TowerLvUp/tower%d/rotatespeed", i);
		ntgu.RotateSpeed = m_LuaCell.getLua<double>(s);


		m_TowerSet.push_back(nt);
		m_TowerGrowTable.push_back(ntgu);
	}
}
