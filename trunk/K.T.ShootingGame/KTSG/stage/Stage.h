//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Stage.h
//  @ Date : 2011/9/6
//  @ Author : 
//
//


#if !defined(_STAGE_H)
#define _STAGE_H
#include "towers/tower.h"
#include "planes/EnemyPlane.h"
#include "bullets/bullet.h"
#include "algo/nway.h"
#include "algo/RandomWay.h"
#include "algo/StraightWay.h"
#include "algo/SwirlWay.h"
#include "algo/TrajectoryAnimator.h"
#include "ball/straight.h"
#include "ball/split.h"
#include "ball/homing.h"
#include "ball/gravity.h"
#include "ball/delay.h"
#include "path/BezierCurve.h"
#include "path/BsplineCurve.h"
#include "path/HSplineCurve.h"
#include "path/LinearLine.h"

struct PlanesFrame
{
	PlanesFrame(){}
	PlanesFrame(float _time, EnemyPlane* _plane)
		:time(_time), plane(_plane){}
	float time;
	EnemyPlane* plane;
	bool operator < (const PlanesFrame& pf)
	{
		return time < pf.time;
	}
};

typedef std::vector<EnemyPlane*> EnemyPlaneptrs;

class Stage
{
public:
	Stage():elpsedtime(0), lastindex(0){}
	void AddEnmyPlane(float time, EnemyPlane* plane);
	void Sort();
	EnemyPlaneptrs GetTimeToGenerateEnmyPlane(float dt);
private:
	std::vector<PlanesFrame>	m_EnemyShips;
	int lastindex;
	float	elpsedtime;
};

#endif  //_STAGE_H