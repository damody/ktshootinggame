//  @ File Name : tour.h
//  @ Date : 2011/8/30
//  @ Author : damody
//
//


#if !defined(_TOUR_H)
#define _TOUR_H
#include "math\OgreVector3.h"
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include <vector>
#include "ball\Ball.h"
#include "algo\Trajectory.h"
#include "ball\behavior.h"

class Tower 
{
public:
	Tower():m_angle(90), m_atkSpeed(0.5), m_atk(10), m_rotateSpeed(90),
		m_elapsedTime(0), m_Trajectory(0), m_Behavior(0)
	{}
	enum tower_type
	{
		NOTHING,
		RAY		// 雷射
	};
	DXVertex	m_pic;		// 要畫的圖
	Texture_Sptr	m_texture;	// 材質
	Texture_Sptr	m_ball_texture;	// 炮彈材質
	BulletVertex	m_ball_pic;
	Ogre::Vector3	m_position;	// 位置
	float		m_angle;	// 射擊方向
	float		m_atkSpeed;	// 攻速(sec)
	float		m_atk;		// 攻擊力
	float		m_rotateSpeed;	// 旋轉速度
	float		m_elapsedTime;	// 經過時間

	Trajectory*	m_Trajectory;
	Behavior*	m_Behavior;

	int		m_maxhp;	// 炮台最大血量
	int		m_hp;		// 炮台血量
	int		m_level;	// 炮台等級
	tower_type	m_type;		// 子彈種類
	
	BallptrVector Update(float dt);
	BallptrVector NewBallptrVector()
	{
		return m_Trajectory->NewBallptrVector();
	}
};

typedef std::vector<Tower> Towers;

#endif  //_TOUR_H
