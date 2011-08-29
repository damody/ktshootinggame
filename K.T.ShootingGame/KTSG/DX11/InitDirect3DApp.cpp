#include "stdafx.h"
#include "InitDirect3DApp.h"

//停止指標
bool stop=false;
//是否顯示說明
bool show=false;

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
: D3DApp(hInstance), m_Width(0), m_Height(0)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
	if( m_DeviceContext )
		m_DeviceContext->ClearState();
	ReleaseCOM(m_DiffuseMapRV);
}

void InitDirect3DApp::initApp()
{
	D3DApp::initApp();
	LoadResource();
	LoadBlend();
	D3DX11CreateShaderResourceViewFromFile(m_d3dDevice, _T("pic//crate.jpg"), 0, 0, &m_DiffuseMapRV, 0);
	buildPointFX();
	buildPoint();
	onResize();
}

void InitDirect3DApp::onResize()
{
	D3DApp::onResize();
	if (m_Width!=NULL && m_Height!=NULL)
	{
		m_Width->SetFloat((float)mClientWidth);
		m_Height->SetFloat((float)mClientHeight);
	}
}

void InitDirect3DApp::updateScene(float dt)
{
	D3DApp::updateScene(dt);
	m_DXUT_UI->UpdataUI(dt);
	m_SwapChain->Present(0, 0);
}

void InitDirect3DApp::DrawScene()
{
	// Set blend
	float BlendFactor[4] = {0,0,0,0};
	m_DeviceContext->OMSetBlendState(m_pBlendState_BLEND, BlendFactor, 0xffffffff);
	//m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);
	static float time = 0.0;
	time += 0.01f;
	D3DApp::DrawScene();
	m_Time->SetFloat(time);
	m_PMap->SetResource(m_DiffuseMapRV);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_PLayout);
	m_PTech->GetPassByIndex(0)->Apply(0,m_DeviceContext);
	UINT stride = sizeof(VertexPoint);
	UINT offset = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Points, &stride, &offset);
	m_DeviceContext->Draw(4, 0);
	
}

void InitDirect3DApp::buildPointFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;
	HRESULT hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\point.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX10CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_TFX2));
	m_PTech = m_TFX2->GetTechniqueByName("PointTech");
	m_Width = m_TFX2->GetVariableByName("width")->AsScalar();
	m_Height =m_TFX2->GetVariableByName("height")->AsScalar();
	m_PMap =m_TFX2->GetVariableByName("gMap")->AsShaderResource();
	m_Time =m_TFX2->GetVariableByName("time")->AsScalar();

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"SIZE",   0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"PI", 0, DXGI_FORMAT_R32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"DIR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	D3DX11_PASS_DESC PassDesc;
	m_PTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	HR(m_d3dDevice->CreateInputLayout(vertexDesc, 4, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &m_PLayout));
}

void InitDirect3DApp::buildPoint()
{
	// set 4 point to show
	std::vector<VertexPoint> Vertex;
	VertexPoint point;
	point.position=D3DXVECTOR3(50,50,0);
	point.size=D3DXVECTOR2(10,20);
	point.angle=0;
	point.direction=D3DXVECTOR3(1,1,0);

	Vertex.push_back(point);

	point.position=D3DXVECTOR3(100,100,0);
	point.size=D3DXVECTOR2(20,10);
	point.angle=10;
	point.direction=D3DXVECTOR3(0,1,0);

	Vertex.push_back(point);

	point.position=D3DXVECTOR3(300,300,0);
	point.size=D3DXVECTOR2(55,55);
	point.angle=30;
	point.direction=D3DXVECTOR3(-1,0,0);

	Vertex.push_back(point);

	point.position=D3DXVECTOR3(300,200,0);
	point.size=D3DXVECTOR2(20,20);
	point.angle=45;
	point.direction=D3DXVECTOR3(0,-1,0);

	Vertex.push_back(point);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(VertexPoint)*Vertex.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride=sizeof(VertexPoint);

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &Vertex[0];
	HR(m_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_Points));
}

void InitDirect3DApp::LoadResource()
{
	m_Lua.InputLuaFile("resource.lua");
	for (int i=1;;++i)
	{
		if (m_Lua.CheckNotNil("pic/%d/1", i))
		{
			int idx = m_Lua.getLua<int>("pic/%d/1", i);
			const char* file = m_Lua.getLua<const char*>("pic/%d/2", i);
			assert(file != 0);
			int getidx = m_TextureManager.AddTexture(file, idx);
			assert(getidx == idx);
		}
		else
			break;
	}
}

void InitDirect3DApp::LoadBlend()
{
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = TRUE;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = FALSE;
	depth_stencil_desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depth_stencil_desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	// 開啟zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteON) )
		return ;

	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	// 關閉zbuffer write
	if ( D3D_OK != m_d3dDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencil_ZWriteOFF) )
		return ;

	CD3D11_BLEND_DESCX blend_state_desc(
		FALSE,
		FALSE,
		TRUE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ONE,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL);
	// ADD混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_ADD) )
		return;
	blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA ;
	blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

	// Alpha Blend混色模式
	if ( D3D_OK != m_d3dDevice->CreateBlendState(&blend_state_desc, &m_pBlendState_BLEND) )
		return ;
}
