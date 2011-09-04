#pragma once
#include "d3dApp.h"
#include "algo/BallptrManager.h"
#include "algo/nway.h"
#include "algo/RandomWay.h"
#include "ball/straight.h"
#include "global.h"
#include <d3dCompiler.h>
#include <d3dx11effect.h>
#include "Vertex.h"
#include "Lua/LuaCell.h"
#include "TextureManager.h"
#include "planes/MainPlane.h"
#include "bullets/bullet.h"
#include "towers/tower.h"
#include "planes/EnemyMainPlane.h"

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();
	void initApp();
private:
		
	void LoadResource();
	void LoadBlend();
	void LoadWarShip();
	void LoadEnemyShips();
	void LoadTowers();
	void buildPointFX();
	void buildPoint();
	void OnResize();

	void DrawScene();
	void UpdateScene(float dt);
	int  UpdateInput();
	int  UpdateWarShip(float dt);
	int  UpdateDeliver(float dt);
	int  UpdateEnemy(float dt);
	int  UpdateBullectMove(float dt);
	int  UpdateBullectCollision();
	int  UpdateUI();
	void PrintInfo();
private:
	ID3DX11EffectShaderResourceVariable*  m_PMap_Warship;
	ID3DX11EffectShaderResourceVariable*  m_PMap_Bullets;

	ID3D11Buffer* m_Buffer_WarShip;
	ID3D11Buffer* m_Buffer_Bullets;
	ID3DX11Effect* m_Effect_Warship;
	ID3DX11Effect* m_Effect_Bullets;
	ID3DX11EffectTechnique* m_PTech_Warship;
	ID3DX11EffectTechnique* m_PTech_Bullets;
	ID3D11InputLayout* m_PLayout_Warship;
	ID3D11InputLayout* m_PLayout_Bullets;
	ID3DX11EffectScalarVariable* m_Warship_Width;
	ID3DX11EffectScalarVariable* m_Warship_Height;
	ID3DX11EffectScalarVariable* m_Bullets_Width;
	ID3DX11EffectScalarVariable* m_Bullets_Height;

	ID3D11BlendState*	m_pBlendState_ADD;
	ID3D11BlendState*	m_pBlendState_BLEND;
	ID3D11DepthStencilState *m_pDepthStencil_ZWriteON;
	ID3D11DepthStencilState *m_pDepthStencil_ZWriteOFF;

	LuaCell			m_Lua;
	DrawVertexGroups	m_DrawVertexGroups;
	MainPlane		m_warShip;
	EnemyMainPlane		m_EnemyMotherShip;
	std::vector<EnemyMainPlane>	m_EnemyShips;

	std::vector<DXVertex>		m_ShipVertex;
	std::vector<BulletVertex>	m_BVertex;
	D3D11_BUFFER_DESC	m_vbd;
};

struct CD3D11_BLEND_DESCX : public D3D11_BLEND_DESC
{
	CD3D11_BLEND_DESCX(){}
	explicit CD3D11_BLEND_DESCX(const D3D11_BLEND_DESC& o) : D3D11_BLEND_DESC( o ){}
	explicit CD3D11_BLEND_DESCX(
		BOOL AlphaToCoverageEnable,
		BOOL IndependentBlendEnable,
		BOOL BlendEnable0,
		D3D11_BLEND SrcBlend0,
		D3D11_BLEND DestBlend0,
		D3D11_BLEND_OP BlendOp0,
		D3D11_BLEND SrcBlendAlpha0,
		D3D11_BLEND DestBlendAlpha0,
		D3D11_BLEND_OP BlendOpAlpha0,
		UINT8 RenderTargetWriteMask0 )
	{
		this->AlphaToCoverageEnable = AlphaToCoverageEnable;
		this->IndependentBlendEnable = IndependentBlendEnable;
		this->RenderTarget[0].BlendEnable = BlendEnable0;
		this->RenderTarget[0].SrcBlend = SrcBlend0;
		this->RenderTarget[0].DestBlend = DestBlend0;
		this->RenderTarget[0].BlendOp = BlendOp0;
		this->RenderTarget[0].SrcBlendAlpha = SrcBlendAlpha0;
		this->RenderTarget[0].DestBlendAlpha = DestBlendAlpha0;
		this->RenderTarget[0].BlendOpAlpha = BlendOpAlpha0;
		this->RenderTarget[0].RenderTargetWriteMask = RenderTargetWriteMask0; 
	}
	~CD3D11_BLEND_DESCX(){}
	operator const D3D11_BLEND_DESC&() const { return *this; }
};

