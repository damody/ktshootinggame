#pragma once
#include "d3dApp.h"
#include <d3dCompiler.h>
#include <d3dx11effect.h>
#include "Vertex.h"
#include "Lua/LuaCell.h"

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
	LuaCell		m_Lua;
};
