//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LoadStage.h
//  @ Date : 2011/9/6
//  @ Author : 
//
//


#if !defined(_LOADSTAGE_H)
#define _LOADSTAGE_H
#include "Lua/LuaCell.h"
#include "Stage.h"

class TrajectoryFactory
{
public:
	enum TrajectoryKind
	{
		TRAJECTORY_ERROR=100,
		NWAY,
		RANDOM_WAY,
		STRAIGHT_WAY,
		SWIR_WAY
	};
	static int Generate(const char* kind, Trajectory* out)
	{
		if (strcmp(kind, "nway"))
		{
			out = new NWay;
			return NWAY;
		}
		else if (strcmp(kind, "randomway"))
		{
			out = new RandomWay;
			return RANDOM_WAY;
		}
		else if (strcmp(kind, "straightway"))
		{
			out = new StraightWay;
			return STRAIGHT_WAY;
		}
		else if (strcmp(kind, "swirlway"))
		{
			out = new SwirlWay;
			return SWIR_WAY;
		}
		return TRAJECTORY_ERROR;
	}
};

class BehaviorFactory
{
	enum BehaviorKind
	{
		BEHAVIOR_ERROR=200,
		STRAIGHT,
		GRAVITY,
		HOMING,
		SPLIT
	};
	static int Generate(const char* kind, Behavior* out)
	{
		if (strcmp(kind, "straight"))
		{
			out = new Straight;
			return STRAIGHT;
		}
		else if (strcmp(kind, "gravity"))
		{
			out = new Gravity;
			return GRAVITY;
		}
		else if (strcmp(kind, "homing"))
		{
			out = new Homing;
			return HOMING;
		}
		else if (strcmp(kind, "split"))
		{
			out = new Split;
			return SPLIT;
		}
		return BEHAVIOR_ERROR;
	}
};

class LoadStage
{
public:
	void LoadNewStage(std::string path, Stage& toStage);
	LuaCell	m_LuaCell;
};

#endif  //_LOADSTAGE_H