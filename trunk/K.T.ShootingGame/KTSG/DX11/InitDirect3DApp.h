#pragma once
#include "d3dApp.h"
#include <d3dCompiler.h>
#include <d3dx11effect.h>
#include "Vertex.h"
#include "Lua/LuaCell.h"
#include "TextureManager.h"

#include "planes/MainPlane.h"

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void DrawScene();
	void LoadResource();
	void LoadBlend();
private:
	void buildPointFX();
	void buildPoint();
private:
	ID3DX11EffectShaderResourceVariable*  m_PMap;
	ID3DX11EffectScalarVariable* m_Time;
	ID3D11ShaderResourceView* m_DiffuseMapRV;

	ID3D11Buffer* m_Points;
	ID3DX11Effect* m_TFX2;
	ID3DX11EffectTechnique* m_PTech;
	ID3D11InputLayout* m_PLayout;
	ID3DX11EffectScalarVariable* m_Width ;
	ID3DX11EffectScalarVariable* m_Height;
	ID3D11BlendState*	m_pBlendState_ADD;
	ID3D11BlendState*	m_pBlendState_BLEND;
	ID3D11DepthStencilState *m_pDepthStencil_ZWriteON;
	ID3D11DepthStencilState *m_pDepthStencil_ZWriteOFF;

	LuaCell		m_Lua;
	TextureManager	m_TextureManager;

	MainPlane* m_warShip;
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
