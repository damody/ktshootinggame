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

class tower {
public:
	enum tower_type
	{
		NOTHING,
		RAY		// 雷射
	};
	DXVertex	m_pic;		// 要畫的圖
	Texture_Sptr	m_texture;	// 材質
	Ogre::Vector3	m_position;	// 位置
	float		m_angle;	// 射擊方向
	float		m_atkSpeed;	// 攻速(sec)
	float		m_atk;		// 攻擊力
	float		m_rotateSpeed;	// 旋轉速度

	int		m_maxhp;	// 炮台最大血量
	int		m_hp;		// 炮台血量
	int		m_level;	// 炮台等級
	tower_type	m_type;		// 子彈種類
	
	
	void Update();
};

#endif  //_TOUR_H
