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
		RAY		// �p�g
	};
	DXVertex	m_pic;		// �n�e����
	Texture_Sptr	m_texture;	// ����
	Ogre::Vector3	m_position;	// ��m
	float		m_angle;	// �g����V
	float		m_atkSpeed;	// ��t(sec)
	float		m_atk;		// �����O
	float		m_rotateSpeed;	// ����t��

	int		m_maxhp;	// ���x�̤j��q
	int		m_hp;		// ���x��q
	int		m_level;	// ���x����
	tower_type	m_type;		// �l�u����
	
	
	void Update();
};

#endif  //_TOUR_H
