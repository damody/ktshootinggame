//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : bullet.h
//  @ Date : 2011/8/30
//  @ Author : 
//
//


#if !defined(_BULLET_H)
#define _BULLET_H
#include "ball\BallptrManager.h"
#include "ball\ball.h"
#include "math\OgreVector3.h"
#include "DX11\Vertex.h"
#include "DX11\TextureManager.h"
#include "memory\VMemPool.h"

class Bullet : public Ball , public CVMemPool<Bullet,200000>
{
public:
	GET_CLASS_SIZE(Behavior)
	inline Bullet(Texture_Sptr texture)
	:Ball(Ogre::Vector3(), 0), m_texture(texture)
	{}
	virtual ~Bullet(){}
	BulletVertex	m_pic;		// 要畫的圖
	Texture_Sptr	m_texture;	// 材質

	bool m_visable;	// 看不看的見
	bool m_enble;	// 子彈有沒有效
	bool m_though;	// 會不會穿透
	bool m_beBeat;	// 會不會被擊中

	int m_atk;	// 攻擊力
	int m_type;	// 子彈類型
	float m_speed;	// 速度
	int m_owner;	// 子彈的主人

	virtual int Update(float dt);
	void UpdateDataToDraw();

	bool operator < (const Bullet& rhs)
	{
		return m_texture < rhs.m_texture;
	}
	bool operator == (const Bullet& rhs)
	{
		return m_texture == rhs.m_texture;
	}
};

bool CompareBullet(const Ball* lhs, const Ball* rhs);

struct DrawVertexGroup
{
	Texture_Sptr	texture;	// 材質
	int	VertexCount, StartVertexLocation;
};
typedef std::vector<DrawVertexGroup> DrawVertexGroups;

#endif  //_BULLET_H bn
