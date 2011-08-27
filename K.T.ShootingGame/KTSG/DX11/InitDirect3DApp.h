#pragma once
#include "d3dApp.h"
#include <d3dCompiler.h>
#include <d3dx11effect.h>
#include "Vertex.h"

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene();
private:
	void buildPointFX();
	void buildPoint();
private:
	ID3DX11EffectShaderResourceVariable*  mPMap;
	ID3DX11EffectScalarVariable* mTime;
	ID3D11ShaderResourceView* mDiffuseMapRV;

	ID3D11Buffer* m_Points;
	ID3DX11Effect* mTFX2;
	ID3DX11EffectTechnique* mPTech;
	ID3D11InputLayout* mPLayout;
	ID3DX11EffectScalarVariable* mWidth ;
	ID3DX11EffectScalarVariable* mHeight;

};
