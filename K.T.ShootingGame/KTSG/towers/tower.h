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
		RAY		// �p�g
	};
	DXVertex	m_pic;		// �n�e����
	Texture_Sptr	m_texture;	// ����
	Texture_Sptr	m_ball_texture;	// ���u����
	BulletVertex	m_ball_pic;
	Ogre::Vector3	m_position;	// ��m
	float		m_angle;	// �g����V
	float		m_atkSpeed;	// ��t(sec)
	float		m_atk;		// �����O
	float		m_rotateSpeed;	// ����t��
	float		m_elapsedTime;	// �g�L�ɶ�

	Trajectory*	m_Trajectory;
	Behavior*	m_Behavior;

	int		m_maxhp;	// ���x�̤j��q
	int		m_hp;		// ���x��q
	int		m_level;	// ���x����
	tower_type	m_type;		// �l�u����
	
	BallptrVector Update(float dt);
	BallptrVector NewBallptrVector()
	{
		return m_Trajectory->NewBallptrVector();
	}
};

typedef std::vector<Tower> Towers;

#endif  //_TOUR_H
