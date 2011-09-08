#pragma once
#include "tower.h"
#include "Lua/LuaCell.h"

struct TowerGrowUp
{
	int Hp;
	float Atk;
	float AtkSpeed;
	float RotateSpeed;
};

class towerFactory
{
private:
	LuaCell m_LuaCell;
	Towers m_TowerSet;	//儲存各種類的砲塔資訊
	int	m_TowerTypeNum;
	std::vector<TowerGrowUp>	m_TowerGrowTable;
public:
	towerFactory();
	Tower NewTower(Tower::tower_type type);
	void TowerLvUp(Tower& tower);
	void Init();
};