#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "InitDirect3DApp.h"
#include "InputState.h"
#include "WaveSound.h"
#include "planes/EnemyPlane.h"
#include "stage/LoadStage.h"
#include "ui/CmdDef.h"

InitDirect3DApp* InitDirect3DApp::dxAppInstance = NULL;

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
: D3DApp(hInstance), m_Warship_Width(0), m_Warship_Height(0), m_Buffer_WarShip(0), m_Buffer_Bullets(0) , m_SettingKeyID(-1), m_LastGameProcess(1), m_GameProcess(1), m_Last2GameProcess(1)
{
	dxAppInstance = this;
}

InitDirect3DApp::~InitDirect3DApp()
{
	if( m_DeviceContext )
		m_DeviceContext->ClearState();
}

void InitDirect3DApp::initApp()
{
	D3DApp::initApp();
	InitTexture();
	LoadResource();
	LoadAllStage();
	LoadBlend();
	LoadWarShip();
	LoadEnemyShips();
	LoadTowers();
	buildPointFX();
	OnResize();
	// Set blend
	float BlendFactor[4] = {0,0,0,0};
	m_DeviceContext->OMSetBlendState(m_pBlendState_BLEND, BlendFactor, 0xffffffff);
	//m_DeviceContext->OMSetDepthStencilState(m_pDepthStencil_ZWriteOFF, 0);
	buildPoint();

	//init control key
	m_CtrlKey.resize(CTRL_KEY_NUM);
	m_CtrlKey[0] = DEFAULT_CTRL_KEY_UP;
	m_CtrlKey[1] = DEFAULT_CTRL_KEY_DOWN ;
	m_CtrlKey[2] = DEFAULT_CTRL_KEY_LEFT ;
	m_CtrlKey[3] = DEFAULT_CTRL_KEY_RIGHT ;
	m_CtrlKey[4] = DEFAULT_CTRL_KEY_SKILL ;
	m_CtrlKey[5] = DEFAULT_CTRL_KEY_TIMECHENGE ;
}


void InitDirect3DApp::UpdateScene(float dt)
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

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
	if (m_Warship_Width!=NULL && m_Warship_Height!=NULL)
	{
		m_Warship_Width->SetFloat((float)mClientWidth);
		m_Warship_Height->SetFloat((float)mClientHeight);
		m_Bullets_Width->SetFloat((float)mClientWidth);
		m_Bullets_Height->SetFloat((float)mClientHeight);
	}
}

void InitDirect3DApp::LoadAllStage()
{
	LoadStage ls;
	ls.LoadNewStage("stage1.lua", m_Stage);
}

void InitDirect3DApp::DrawScene()
{
	// clear color
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	// we don't need depth
	//m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_DeviceContext->ClearRenderTargetView(RTVView1, m_ClearColor);
	m_DeviceContext->ClearRenderTargetView(RTVView2, m_ClearColor);
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
	UINT stride = sizeof(DXVertex);
	UINT offset = 0;
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_PLayout_Warship);
	//m_DeviceContext->OMSetRenderTargets(1,&RTVView2,m_DepthStencilView2); // draw all ship
	m_PTech_Warship->GetPassByIndex(0)->Apply(0, m_DeviceContext);
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_WarShip, &stride, &offset);
	m_PMap_Warship->SetResource(*(m_motherShip.m_texture));
	m_DeviceContext->Draw(1 + (UINT)m_warShips.size() + (UINT)m_EnemyShips.size(), 0);
	UINT stride2 = sizeof(BulletVertex);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_DeviceContext->IASetInputLayout(m_PLayout_Bullets);
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_Buffer_Bullets, &stride2, &offset);
	//m_DeviceContext->OMSetRenderTargets(1,&RTVView1,m_DepthStencilView2); // draw all bullet
	for (DrawVertexGroups::iterator it = m_DrawVertexGroups.begin();
		it != m_DrawVertexGroups.end();++it)
	{
		if (it->texture.get())
		{
			m_PMap_Bullets->SetResource(*(it->texture));
			m_PTech_Bullets->GetPassByIndex(0)->Apply(0, m_DeviceContext);
			m_DeviceContext->Draw(it->VertexCount, it->StartVertexLocation);
		}
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

	hr=D3DX11CompileFromFile(_T("screen.fx"), NULL, NULL, NULL, 
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
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, m_d3dDevice, &m_Effect_Collion));

	m_PTech_Collion = m_Effect_Collion->GetTechniqueByName("PointTech");
	m_PMap_Collion1 =m_Effect_Collion->GetVariableByName("gMap1")->AsShaderResource();
	m_PMap_Collion2 =m_Effect_Collion->GetVariableByName("gMap2")->AsShaderResource();

	m_PTech_Collion->GetPassByIndex(0)->GetDesc(&PassDesc2);
	HR(m_d3dDevice->CreateInputLayout(VertexDesc_SVertex, 2, PassDesc2.pIAInputSignature,
		PassDesc2.IAInputSignatureSize, &m_PLayout_Collion));

	m_vbd.Usage = D3D11_USAGE_IMMUTABLE;
	m_vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_vbd.CPUAccessFlags = 0;
	m_vbd.MiscFlags = 0;
}



void InitDirect3DApp::buildPoint()
{
	ReleaseCOM(m_Buffer_WarShip);
	ReleaseCOM(m_Buffer_Bullets);
	// set warship
	m_ShipVertex.clear();
	m_ShipVertex.push_back(m_motherShip.m_pic);

	for(std::vector<MainPlane>::iterator it = m_warShips.begin();
		it != m_warShips.end(); it++)
	{
		m_ShipVertex.push_back(it->m_pic);
	}

	for(std::vector<EnemyPlane*>::iterator it = m_EnemyShips.begin();
		it != m_EnemyShips.end(); it++)
	{
		m_ShipVertex.push_back((*it)->m_pic);
	}
	m_vbd.ByteWidth = (UINT)(sizeof(DXVertex)*m_ShipVertex.size());
	m_vbd.StructureByteStride=sizeof(DXVertex);
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &m_ShipVertex[0];
	HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_WarShip));

	// save each vertex groups's texture
	m_DrawVertexGroups.clear();
	DrawVertexGroup dvg;
	int vertexCount = 0, count = 0;
	if (!g_BallptrManager.Empty())
	{
		dvg.texture = ((Bullet*)g_BallptrManager.Ballptrs().front())->m_texture;
		dvg.StartVertexLocation = 0;
		// save all vertex points
		m_BVertex.clear();
		const BallptrVector& vec = g_BallptrManager.Ballptrs();
		for (BallptrVector::const_iterator it = vec.begin();
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
			m_BVertex.push_back(((Bullet*)(*it))->m_pic);
		}
		// save finally dvg
		dvg.VertexCount = vertexCount;
		m_DrawVertexGroups.push_back(dvg);
		// debug mother collison
		vertexCount = 3;
		dvg.StartVertexLocation = count;
		count += 3;
		BulletVertex pic =((Bullet*)vec.front())->m_pic;
		Polygon2D poly = m_motherShip.m_Polygon2D;
		poly.Offset(m_motherShip.m_position);
		pic.size.x = 30;
		pic.size.y = 30;
		pic.angle = m_motherShip.m_Polygon2D.GetAngle();
		pic.position.x = poly.Points()[0].x;
		pic.position.y = poly.Points()[0].y;
		m_BVertex.push_back(pic);
		pic.position.x = poly.Points()[1].x;
		pic.position.y = poly.Points()[1].y;
		m_BVertex.push_back(pic);
		pic.position.x = poly.Points()[2].x;
		pic.position.y = poly.Points()[2].y;
		m_BVertex.push_back(pic);
		dvg.VertexCount = vertexCount;
		m_DrawVertexGroups.push_back(dvg);
	}

	// save enemy ball
	if (!g_EnemyBallptrManager.Empty())
	{
		dvg.texture = ((Bullet*)g_EnemyBallptrManager.Ballptrs().front())->m_texture;
		dvg.StartVertexLocation = count;
		// save all vertex points
		const BallptrVector& vec = g_EnemyBallptrManager.Ballptrs();
		vertexCount = 0;
		for (BallptrVector::const_iterator it = vec.begin();
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
			m_BVertex.push_back(((Bullet*)(*it))->m_pic);
		}
		// save finally dvg
		dvg.VertexCount = vertexCount;
		m_DrawVertexGroups.push_back(dvg);
	}
	if (vertexCount>0)
	{
		// save other info
		m_vbd.ByteWidth = (UINT)(sizeof(BulletVertex)*m_BVertex.size());
		m_vbd.StructureByteStride=sizeof(BulletVertex);
		vinitData.pSysMem = &m_BVertex[0];
		HR(m_d3dDevice->CreateBuffer(&m_vbd, &vinitData, &m_Buffer_Bullets));
	}
}

void InitDirect3DApp::LoadResource()
{
	m_Lua.InputLuaFile("resource.lua");
	// load pic
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
	// load wav file
	WavSoundS::instance().Initialize(m_hMainWnd);
	WavSoundS::instance().SetVolume(-2000);
	for (int i=1;;++i)
	{
		if (m_Lua.CheckNotNil("wav/%d/1", i))
		{
			int idx = m_Lua.getLua<int>("wav/%d/1", i);
			const char* file = m_Lua.getLua<const char*>("wav/%d/2", i);
			int mutiplay = m_Lua.getLua<int>("wav/%d/3", i);
			assert(file != 0);
			bool res = WavSoundS::instance().CreatSound(file, idx, mutiplay);
			assert(res);
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
	m_motherShip.m_angle = 0;
	m_motherShip.m_h = 350;
	m_motherShip.m_w = 600;
	m_motherShip.m_position.x = 500;
	m_motherShip.m_position.y = 200;
	m_motherShip.m_texture = g_TextureManager.GetTexture(102);

	MainPlane ship;
	ship.m_texture = g_TextureManager.GetTexture(102);
	ship.m_angle = 180;
	ship.m_h = 70;
	ship.m_w = 120;
	ship.motherShip = &m_motherShip;
}

void InitDirect3DApp::LoadEnemyShips()
{
}

void InitDirect3DApp::LoadTowers()
{
	Tower t;
	Straight* st = new Straight;
	Towers ts;
	st->mVelocity = 400;
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
	t.m_ball_pic.size.x = 50;
	t.m_ball_pic.size.y = 50;
	t.m_atkSpeed = 0.5;
	//ts.push_back(t);
	
	t.m_ball_texture = g_TextureManager.GetTexture(103);
	t.m_ball_pic.picpos.x = 1;
	t.m_ball_pic.picpos.y = 1;
	t.m_ball_pic.picpos.z = 2;
	t.m_ball_pic.picpos.w = 2;
	t.m_ball_pic.size.x = 2;
	t.m_ball_pic.size.y = 20;
	t.m_atkSpeed = 0.05f;
	t.m_Trajectory = new NWay(1, Ogre::Vector3(0,0,0), Ogre::Vector3(0,1,0));
	t.m_Trajectory->SetBehavior(t.m_Behavior);
	t.m_Trajectory->mPolygon.AddPoint(0,0);
	t.m_Trajectory->mPolygon.AddPoint(0,20);
	//t.m_Trajectory->mPolygon.AddPoint(1,80);

	m_Lua.InputLuaFile("tower.lua");
	float tx,ty;
	t.m_hp = 10000;
	t.m_type = Tower::MACHINE_GUN;
	t.m_level = 1;
	t.m_atk = 1.0f/100;
	for (int i=0; i<13; i++)
	{
		if (i==3)
			t.m_type = Tower::NOTHING;
		tx = (float)m_Lua.getLua<double>("TowerPos/Tpos%d/px", i+1);
		ty = (float)m_Lua.getLua<double>("TowerPos/Tpos%d/py", i+1);
		t.m_position = Ogre::Vector3(tx, ty, 0);
		ts.push_back(t);
	}
	m_motherShip.m_Towers = ts;
	m_motherShip.InitTowerFactory();
}

int InitDirect3DApp::UpdateInput()
{
	InputStateS::instance().GetInput();
	static int sound = -2000;
	if (InputStateS::instance().isKeyDown(KEY_NUMPAD1))
	{
		sound += 500;
		WavSoundS::instance().SetVolume(sound);
		printf("%d\n", sound);
	}
	if (InputStateS::instance().isKeyDown(KEY_NUMPAD2))
	{
		sound -= 500;
		WavSoundS::instance().SetVolume(sound);
		printf("%d\n", sound);
	}
	return 0;
}

int InitDirect3DApp::UpdateWarShip( float dt )
{
	m_motherShip.Update(dt);
	for(std::vector<MainPlane>::iterator it = m_warShips.begin();
		it != m_warShips.end(); it++)
	{
		it->Update(dt);
	}
	return 0;
}

int InitDirect3DApp::UpdateDeliver( float dt )
{
	return 0;
}

int InitDirect3DApp::UpdateEnemy( float dt )
{
	EnemyPlaneptrs eps = m_Stage.GetTimeToGenerateEnmyPlane(dt);
	if (!eps.empty())
	{
		std::copy(eps.begin(), eps.end(), std::back_inserter(m_EnemyShips));
	}
	for(EnemyPlaneptrs::iterator it = m_EnemyShips.begin();
		it != m_EnemyShips.end();it++)
	{
		(*it)->Update(dt);
		Polygon2D poly = (*it)->m_Polygon2D;
		poly.Offset((*it)->m_position);
	}
	return 0;
}

int InitDirect3DApp::UpdateBullectMove( float dt )
{
	// update all ball
	g_BallptrManager.Update(dt);
	// free delete ball
	BallptrVector& bv = g_BallptrManager.mDeleteVector;
	for (BallptrVector::iterator it = bv.begin();it != bv.end();++it)
		delete *it;
	bv.clear();
	g_BallptrManager.Sort(CompareBullet);
	// update enemy ball
	g_EnemyBallptrManager.Update(dt);
	BallptrVector& bv2 = g_EnemyBallptrManager.mDeleteVector;
	for (BallptrVector::iterator it = bv2.begin();it != bv2.end();++it)
		delete *it;  
	bv2.clear();
	g_EnemyBallptrManager.Sort(CompareBullet);
	return 0;
}

int InitDirect3DApp::UpdateBullectCollision()
{
	Polygon2D poly = m_motherShip.m_Polygon2D;
	poly.Offset(m_motherShip.m_position);
	//std::cout << poly.Points()[2] << std::endl;
	g_EnemyBallptrManager.SortCollision();
	BallptrVector ans = g_EnemyBallptrManager.GetCollision(poly);
	for (size_t i=0;i < ans.size();++i)
	{
		ans[i]->mBallStatus = Ball::DESTORY;
	}
	return 0;
}

int InitDirect3DApp::UpdateUI()
{
	switch(m_GameProcess)
	{
	case UI_PAGE_MAIN_MENU:
		DealMainMenu();
		break;
	case UI_PAGE_OPTION:
		DealOptionPage();
		break;
	case UI_PAGE_TOWER_SETTING:
		DealTowerSettingPage();
		break;
	case UI_PAGE_GAME_PLAY:
		DealGamePlayPage();
		break;
	}
	m_DXUT_UI->ClearCmdState();
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
		std::wcout << L"FPS: " << fps << L" Balls: " << g_BallptrManager.Ballptrs().size()
			 << "\t"<< g_EnemyBallptrManager.Ballptrs().size() << L"\n";
		std::wcout << m_FrameStats;
		// Reset for next average.
		frameCnt = 0;
		t_base  += 1.0f;
	}
}


void InitDirect3DApp::InitTexture()
{
	ID3D11Texture2D* tex1, *tex2, *tesres;
	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc0;
	depthStencilDesc0.Width     = mClientWidth;
	depthStencilDesc0.Height    = mClientHeight;
	depthStencilDesc0.MipLevels = 1;
	depthStencilDesc0.ArraySize = 1;
	depthStencilDesc0.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	depthStencilDesc0.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc0.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc0.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc0.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	depthStencilDesc0.CPUAccessFlags = 0; 
	depthStencilDesc0.MiscFlags      = 0;
	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc0, 0, &tex1));
	HR(m_d3dDevice->CreateShaderResourceView(tex1, 0, &SRVView1));
	HR(m_d3dDevice->CreateRenderTargetView(tex1, 0, &RTVView1));

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc0, 0, &tex2));
	HR(m_d3dDevice->CreateShaderResourceView(tex2, 0, &SRVView2));
	HR(m_d3dDevice->CreateRenderTargetView(tex2, 0, &RTVView2));

	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc0, 0, &tesres));
	HR(m_d3dDevice->CreateShaderResourceView(tesres, 0, &SRVViewRes));
	HR(m_d3dDevice->CreateRenderTargetView(tesres, 0, &RTVViewRes));

	Screen_Vertex svQuad[4];
	svQuad[0].pos = D3DXVECTOR4( -1.0f, 1.0f, 0.5f, 1.0f );
	svQuad[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	svQuad[1].pos = D3DXVECTOR4( 1.0f, 1.0f, 0.5f, 1.0f );
	svQuad[1].tex = D3DXVECTOR2( 1.0f, 0.0f );
	svQuad[2].pos = D3DXVECTOR4( -1.0f, -1.0f, 0.5f, 1.0f );
	svQuad[2].tex = D3DXVECTOR2( 0.0f, 1.0f );
	svQuad[3].pos = D3DXVECTOR4( 1.0f, -1.0f, 0.5f, 1.0f );
	svQuad[3].tex = D3DXVECTOR2( 1.0f, 1.0f );

	ID3D11Texture2D* tex12;

	D3D11_TEXTURE2D_DESC depthStencilDesc1;
	depthStencilDesc1.Width     = mClientWidth;
	depthStencilDesc1.Height    = mClientHeight;
	depthStencilDesc1.MipLevels = 1;
	depthStencilDesc1.ArraySize = 1;
	depthStencilDesc1.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc1.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc1.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc1.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc1.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc1.CPUAccessFlags = 0; 
	depthStencilDesc1.MiscFlags      = 0;
	HR(m_d3dDevice->CreateTexture2D(&depthStencilDesc1, 0, &tex12));
	HR(m_d3dDevice->CreateDepthStencilView(tex12, 0, &m_DepthStencilView2));
}

void InitDirect3DApp::SetCtrlKey()
{
	if (InputStateS::instance().isKeyPress(KEY_A))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_A;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "A");
	}
	else if (InputStateS::instance().isKeyPress(KEY_B))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_B;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "B");
	}
	else if (InputStateS::instance().isKeyPress(KEY_C))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_C;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "C");
	}
	else if (InputStateS::instance().isKeyPress(KEY_D))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_D;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "D");
	}
	else if (InputStateS::instance().isKeyPress(KEY_E))
	{
		m_CtrlKey[m_SettingKeyID] = KEY_E;
		m_SettingKeyID=-1;
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "E");
	}
	else if (InputStateS::instance().isKeyPress(KEY_F)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_F; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "F");
	}
	else if (InputStateS::instance().isKeyPress(KEY_G)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_G; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "G");
	}
	else if (InputStateS::instance().isKeyPress(KEY_H)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_H; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "H");
	}
	else if (InputStateS::instance().isKeyPress(KEY_I)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_I; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "I");
	}
	else if (InputStateS::instance().isKeyPress(KEY_J)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_J; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "J");
	}
	else if (InputStateS::instance().isKeyPress(KEY_K)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_K; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "K");
	}
	else if (InputStateS::instance().isKeyPress(KEY_L)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_L; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "L");
	}
	else if (InputStateS::instance().isKeyPress(KEY_M)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_M; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "M");
	}
	else if (InputStateS::instance().isKeyPress(KEY_N)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_N; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "N");
	}
	else if (InputStateS::instance().isKeyPress(KEY_O)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_O; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "O");
	}
	else if (InputStateS::instance().isKeyPress(KEY_P)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_P; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "P");
	}
	else if (InputStateS::instance().isKeyPress(KEY_Q)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_Q; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Q");
	}
	else if (InputStateS::instance().isKeyPress(KEY_R)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_R; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "R");
	}
	else if (InputStateS::instance().isKeyPress(KEY_S)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_S; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "S");
	}
	else if (InputStateS::instance().isKeyPress(KEY_T)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_T; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "T");
	}
	else if (InputStateS::instance().isKeyPress(KEY_U)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_U; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "U");
	}
	else if (InputStateS::instance().isKeyPress(KEY_V)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_V; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "V");
	}
	else if (InputStateS::instance().isKeyPress(KEY_W)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_W; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "W");
	}
	else if (InputStateS::instance().isKeyPress(KEY_X)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_X; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "X");
	}
	else if (InputStateS::instance().isKeyPress(KEY_Y)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_Y; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Y");
	}
	else if (InputStateS::instance().isKeyPress(KEY_Z)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_Z; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Z");
	}
	//===============================================================================0~9===================================================================
	//===============================================================================0~9===================================================================
	else if (InputStateS::instance().isKeyPress(KEY_0)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_0; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "0");
	}
	else if (InputStateS::instance().isKeyPress(KEY_1)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_1; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "1");
	}
	else if (InputStateS::instance().isKeyPress(KEY_2)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_2; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "2");
	}
	else if (InputStateS::instance().isKeyPress(KEY_3)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_3; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "3");
	}
	else if (InputStateS::instance().isKeyPress(KEY_4)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_4; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "4");
	}
	else if (InputStateS::instance().isKeyPress(KEY_5)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_5; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "5");
	}
	else if (InputStateS::instance().isKeyPress(KEY_6)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_6; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "6");
	}
	else if (InputStateS::instance().isKeyPress(KEY_7)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_7; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "7");
	}
	else if (InputStateS::instance().isKeyPress(KEY_8)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_8; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "8");
	}
	else if (InputStateS::instance().isKeyPress(KEY_9)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_9; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "9");
	}
	//===============================================================================numpad===================================================================
	//===============================================================================numpad===================================================================
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD0)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD0; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num0");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD1)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD1; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num1");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD2)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD2; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num2");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD3)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD3; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num3");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD4)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD4; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num4");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD5)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD5; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num5");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD6)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD6; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num6");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD7)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD7; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num7");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD8)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD8; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num8");
	}
	else if (InputStateS::instance().isKeyPress(KEY_NUMPAD9)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_NUMPAD9; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "num9");
	}
	//===============================================================================方向鍵===================================================================
	//===============================================================================方向鍵===================================================================
	else if (InputStateS::instance().isKeyPress(KEY_UP)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_UP; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Up");
	}
	else if (InputStateS::instance().isKeyPress(KEY_DOWN)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_DOWN; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Down");
	}
	else if (InputStateS::instance().isKeyPress(KEY_LEFT)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_LEFT; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Left");
	}
	else if (InputStateS::instance().isKeyPress(KEY_RIGHT)) 
	{
		m_CtrlKey[m_SettingKeyID] = KEY_RIGHT; 
		m_SettingKeyID=-1; 
		m_DXUT_UI->SetStatic(m_SettingKeyTextID, "Right");
	}
	if (m_SettingKeyID==-1)
		m_motherShip.m_CtrlKey = m_CtrlKey;
}

void InitDirect3DApp::DealMainMenu()
{
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_MAIN_MENU_STARTGAME:
			ChangeUI(UI_PAGE_GAME_PLAY);
			break;
		case IDC_MAIN_MENU_OPTION:
			ChangeUI(UI_PAGE_OPTION);
			break;
		case IDC_MAIN_MENU_EXIT:
			exit(0);
			break;
		}
	}
}

void InitDirect3DApp::DealOptionPage()
{
	int val;
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();

	if (m_SettingKeyID>=0)
		SetCtrlKey();		//設定控制按鍵的處理函數

	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_OPTION_MENU_VOLUME:
			val = m_DXUT_UI->GetSliderNum(cmdstate[i].id)-7000;
			WavSoundS::instance().SetVolume(val);
			break;
		case IDC_OPTION_MENU_KEY_UP:
			m_SettingKeyID = 0;
			m_SettingKeyTextID = IDC_OPTION_MENU_KEY_UP-1;
			break;
		case IDC_OPTION_MENU_KEY_DOWN:
			m_SettingKeyID = 1;
			m_SettingKeyTextID = IDC_OPTION_MENU_KEY_DOWN-1;
			break;
		case IDC_OPTIOT_MENU_KEY_LEFT:
			m_SettingKeyID = 2;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_LEFT-1;
			break;
		case IDC_OPTIOT_MENU_KEY_RIGHT:
			m_SettingKeyID = 3;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_RIGHT-1;
			break;
		case IDC_OPTIOT_MENU_KEY_SKILL:
			m_SettingKeyID = 4;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_SKILL-1;
			break;
		case IDC_OPTIOT_MENU_KEY_TIME:
			m_SettingKeyID = 5;
			m_SettingKeyTextID = IDC_OPTIOT_MENU_KEY_TIME-1;
			break;
		case IDC_OPTIOT_MENU_KEY_EXIT:
			GoBackUI();
			break;
		}
	}
}

void InitDirect3DApp::DealTowerSettingPage()
{
	int tid;
	Tower::tower_type ttype;
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();
	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_TOWER_SETTING_TOWERCOMBO:
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_LVUP:
			tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
			m_motherShip.TowerLvUp(tid);
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_SELL:
			tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
			m_motherShip.SellTower(tid);
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_TOWERSEL:
			break;
		case IDC_TOWER_SETTING_BUY:
			tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
			ttype = (Tower::tower_type)(m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERSEL)+1);
			m_motherShip.BuyTower(tid, ttype);
			ReflashTowerState();
			break;
		case IDC_TOWER_SETTING_OPTION:
			ChangeUI(UI_PAGE_OPTION);
			break;
		case IDC_TOWER_SETTING_BACK:
			GoBackUI();
			break;
		case IDC_TOWER_SETTING_EXIT:
			exit(0);
			break;
		}
	}
}

void InitDirect3DApp::DealGamePlayPage()
{
	std::vector<CmdState> cmdstate = m_DXUT_UI->GetCmdState();
	for (size_t i=0; i<cmdstate.size(); i++)
	{
		switch(cmdstate[i].id)
		{
		case IDC_PLAY_PAGE_MENU:
			ChangeUI(UI_PAGE_TOWER_SETTING);
			break;
		}
	}

	int hp;
	char c[36];
	for (size_t i=0; i<m_motherShip.m_Towers.size(); i++)
	{
		hp = m_motherShip.m_Towers[i].m_hp;
		sprintf_s(c, 36, "hp:%d", hp);
		m_DXUT_UI->SetStatic(IDC_PLAY_PAGE_TEXT_T1HP+i*2, c);
	}
}

void InitDirect3DApp::ChangeUI( int i )
{
	if (i!=m_GameProcess)
	{
		m_Last2GameProcess = m_LastGameProcess;
		m_LastGameProcess = m_GameProcess;
		m_GameProcess=i;
		m_DXUT_UI->CloseAllUI();
		m_DXUT_UI->OpenUI(i);
	}
}

void InitDirect3DApp::GoBackUI()
{
	if (m_LastGameProcess!=m_GameProcess)
	{
		m_GameProcess=m_LastGameProcess;
		m_LastGameProcess=m_Last2GameProcess;
		m_DXUT_UI->CloseAllUI();
		m_DXUT_UI->OpenUI(m_GameProcess);
	}
}

void InitDirect3DApp::ReflashTowerState()
{
	int tid, tlv, thp;
	float tatk,tatkspeed;
	Tower::tower_type ttype;
	char s[36];

	tid = m_DXUT_UI->GetComboBoxSel(IDC_TOWER_SETTING_TOWERCOMBO);
	ttype = m_motherShip.m_Towers[tid].m_type;
	tlv = m_motherShip.m_Towers[tid].m_level;
	thp = m_motherShip.m_Towers[tid].m_hp;
	tatk = m_motherShip.m_Towers[tid].m_atk;
	tatkspeed = m_motherShip.m_Towers[tid].m_atkSpeed;
	switch(ttype)
	{
	case Tower::RAY:
		sprintf_s(s, 36, "Type:Laser");
		break;
	case Tower::MACHINE_GUN:
		sprintf_s(s, 36, "Type:Machine gun");
		break;
	case Tower::MISSILE:
		sprintf_s(s, 36, "Type:Missile");
		break;
	}
	if (ttype == Tower::NOTHING)
	{
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_TYPE, "Type:--");
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_HP, "Hp:--");
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_LV, "Lv:--");
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_ATK, "Atk:--");
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_ATKSP, "Atk speed:--");
	}
	else
	{
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_TYPE, s);
		sprintf_s(s, 36, "Hp:%d", thp);
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_HP, s);
		sprintf_s(s, 36, "Lv:%d", tlv);
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_LV, s);
		sprintf_s(s, 36, "Atk:%f", tatk);
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_ATK, s);
		sprintf_s(s, 36, "Atk speed:%f", tatkspeed);
		m_DXUT_UI->SetStatic(IDC_TOWER_SETTING_TEXT_ATKSP, s);
	}
}
