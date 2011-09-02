#include "stdafx.h"
#include "InitDirect3DApp.h"
#include "InputState.h"

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
: D3DApp(hInstance), m_Warship_Width(0), m_Warship_Height(0), m_Buffer_WarShip(0), m_Buffer_Bullets(0) 
{
}

InitDirect3DApp::~InitDirect3DApp()
{
	if( m_DeviceContext )
		m_DeviceContext->ClearState();
}

void InitDirect3DApp::initApp()
{
	D3DApp::initApp();
	LoadResource();
	LoadBlend();
	LoadWarShip();
	LoadTowers();
	buildPointFX();
	onResize();
	// Set blend
	float BlendFactor[4] = {0,0,0,0};
	m_DeviceContext->OMSetBlendState(m_pBlendState_BLEND, BlendFactor, 0xffffffff);
	//m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);
	buildPoint();
}

void InitDirect3DApp::onResize()
{
	D3DApp::onResize();
	if (m_Warship_Width!=NULL && m_Warship_Height!=NULL)
	{
		m_Warship_Width->SetFloat((float)mClientWidth);
		m_Warship_Height->SetFloat((float)mClientHeight);
		m_Bullets_Width->SetFloat((float)mClientWidth);
		m_Bullets_Height->SetFloat((float)mClientHeight);
	}
}

void InitDirect3DApp::updateScene(float dt)
{
	m_DXUT_UI->UpdataUI(dt);
	m_SwapChain->Present(0, 0);
	D3DApp::DrawScene(); // clear window
	PrintInfo();
	UpdateInput();
	UpdateWarShip(dt);
	UpdateDeliver(dt);
	UpdateEnemy(dt);
	UpdateBullectMove(dt);
	UpdateBullectCollision();
	UpdateUI();
	buildPoint();
}

void InitDirect3DApp::DrawScene()
{
	UINT stride = sizeof(DXVertex);
	UINT offset = 0;
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_PLayout_Warship);
	m_PTech_Warship->GetPassByIndex(0)->Apply(0, m_DeviceContext);
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_WarShip, &stride, &offset);
	m_PMap_Warship->SetResource(*(m_warShip.m_texture));
	m_DeviceContext->Draw(1, 0);
	UINT stride2 = sizeof(BulletVertex);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_PLayout_Bullets);
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Bullets, &stride2, &offset);
	for (DrawVertexGroups::iterator it = m_DrawVertexGroups.begin();
		it != m_DrawVertexGroups.end();++it)
	{
		m_PMap_Bullets->SetResource(*(it->texture));
		m_PTech_Bullets->GetPassByIndex(0)->Apply(0, m_DeviceContext);
		m_DeviceContext->Draw(it->VertexCount, it->StartVertexLocation);
	}
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
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Warship));
	m_PTech_Warship = m_Effect_Warship->GetTechniqueByName("PointTech");
	m_Warship_Width = m_Effect_Warship->GetVariableByName("width")->AsScalar();
	m_Warship_Height =m_Effect_Warship->GetVariableByName("height")->AsScalar();
	m_PMap_Warship =m_Effect_Warship->GetVariableByName("gMap")->AsShaderResource();

	D3DX11_PASS_DESC PassDesc;
	m_PTech_Warship->GetPassByIndex(0)->GetDesc(&PassDesc);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_DXVertex, 3, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &m_PLayout_Warship));

	hr=D3DX11CompileFromFile(_T("shader\\bullet.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX11CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Bullets));
	
	m_PTech_Bullets = m_Effect_Bullets->GetTechniqueByName("PointTech");
	m_Bullets_Width = m_Effect_Bullets->GetVariableByName("width")->AsScalar();
	m_Bullets_Height =m_Effect_Bullets->GetVariableByName("height")->AsScalar();
	m_PMap_Bullets =m_Effect_Bullets->GetVariableByName("gMap")->AsShaderResource();

	D3DX11_PASS_DESC PassDesc2;
	m_PTech_Bullets->GetPassByIndex(0)->GetDesc(&PassDesc2);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_BulletVertex, 4, PassDesc2.pIAInputSignature,
		PassDesc2.IAInputSignatureSize, &m_PLayout_Bullets));
}

void InitDirect3DApp::buildPoint()
{
	ReleaseCOM(m_Buffer_WarShip);
	ReleaseCOM(m_Buffer_Bullets);
	// set warship
	std::vector<DXVertex> Vertex;
	Vertex.push_back(m_warShip.m_pic);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(DXVertex)*Vertex.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride=sizeof(DXVertex);

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &Vertex[0];
	HR(m_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_Buffer_WarShip));

	if (!g_BallptrManager.mBallptrVector.empty())
	{
		// save each vertex groups's texture
		m_DrawVertexGroups.clear();
		DrawVertexGroup dvg;
		dvg.texture = ((Bullet*)*(g_BallptrManager.mBallptrVector.begin()))->m_texture;
		dvg.StartVertexLocation = 0;
		// save all vertex points
		std::vector<BulletVertex> BVertex;
		BallptrVector& vec = g_BallptrManager.mBallptrVector;
		int vertexCount = 0, count = 0;
		for (BallptrVector::iterator it = vec.begin();
			it != vec.end(); ++it)
		{
			if (((Bullet*)(*it))->m_texture != dvg.texture)
			{
				dvg.VertexCount = vertexCount;
				m_DrawVertexGroups.push_back(dvg);
				vertexCount = 0;
				// save next info
				dvg.StartVertexLocation = count;
				dvg.texture = ((Bullet*)(*it))->m_texture;
			}
			++vertexCount;
			++count;
			BVertex.push_back(((Bullet*)(*it))->m_pic);
		}
		// save finally dvg
		dvg.VertexCount = vertexCount;
		m_DrawVertexGroups.push_back(dvg);
		// save other info
		vbd.ByteWidth = sizeof(BulletVertex)*BVertex.size();
		vinitData.pSysMem = &BVertex[0];
		HR(m_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_Buffer_Bullets));
	}
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
			int getidx = g_TextureManager.AddTexture(file, idx);
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

void InitDirect3DApp::LoadWarShip()
{
	m_warShip.m_angle = 0;
	m_warShip.m_h = 350;
	m_warShip.m_w = 600;
	m_warShip.m_position.x = 800;
	m_warShip.m_position.y = 200;
	m_warShip.m_texture = g_TextureManager.GetTexture(102);
}

int InitDirect3DApp::LoadTowers()
{
	Tower t;
	Straight* st = new Straight;
	st->mVelocity = 500;
	t.m_Behavior = st;
	t.m_Trajectory = new NWay(5, Ogre::Vector3(0,0,0), Ogre::Vector3(0,1,0));
	t.m_Trajectory->SetBehavior(t.m_Behavior);
	t.m_position = Ogre::Vector3(-100, 0, 0);
	t.m_texture = g_TextureManager.GetTexture(104);
	t.m_ball_texture = g_TextureManager.GetTexture(100);
	t.m_ball_pic.picpos.x = 3;
	t.m_ball_pic.picpos.y = 1;
	t.m_ball_pic.picpos.z = 4;
	t.m_ball_pic.picpos.w = 2;
	t.m_ball_pic.size.x = 25;
	t.m_ball_pic.size.y = 25;
	t.m_atkSpeed = 0.5;
	Towers ts;
	ts.push_back(t);
	t.m_position = Ogre::Vector3(100, 0, 0);
	t.m_ball_texture = g_TextureManager.GetTexture(103);
	t.m_ball_pic.picpos.x = 1;
	t.m_ball_pic.picpos.y = 1;
	t.m_ball_pic.picpos.z = 2;
	t.m_ball_pic.picpos.w = 2;
	t.m_ball_pic.size.x = 20;
	t.m_ball_pic.size.y = 200;
	t.m_atkSpeed = 0.2;
	t.m_Trajectory = new NWay(3, Ogre::Vector3(0,0,0), Ogre::Vector3(0,1,0));
	t.m_Trajectory->SetBehavior(t.m_Behavior);
	ts.push_back(t);
	m_warShip.m_Towers = ts;
	return 0;
}

int InitDirect3DApp::UpdateInput()
{
	InputStateS::instance().GetInput();
	return 0;
}

int InitDirect3DApp::UpdateWarShip( float dt )
{
	m_warShip.Update(dt);
	return 0;
}

int InitDirect3DApp::UpdateDeliver( float dt )
{
	return 0;
}

int InitDirect3DApp::UpdateEnemy( float dt )
{
	return 0;
}

int InitDirect3DApp::UpdateBullectMove( float dt )
{
	// update all ball
	g_BallptrManager.Update(dt);
	// free delete ball
	BallptrVector& bv = g_BallptrManager.mDeleteVector;
	for (BallptrVector::iterator it = bv.begin();
		it != bv.end();++it)
	{
		Bullet::pool.destroy((Bullet*)(*it));
	}
	bv.clear();
	std::sort(g_BallptrManager.mBallptrVector.begin(), g_BallptrManager.mBallptrVector.end(), CompareBullet);
	return 0;
}

int InitDirect3DApp::UpdateBullectCollision()
{
	return 0;
}

int InitDirect3DApp::UpdateUI()
{
	return 0;
}

void InitDirect3DApp::PrintInfo()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.
	static int frameCnt = 0;
	static float t_base = 0.0f;
	frameCnt++;
	// Compute averages over one second period.
	if( (m_Timer.getGameTime() - t_base) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::wcout << L"FPS: " << fps << L" Balls: " << g_BallptrManager.mBallptrVector.size() << L"\n";
		std::wcout << m_FrameStats;
		// Reset for next average.
		frameCnt = 0;
		t_base  += 1.0f;
	}
}
