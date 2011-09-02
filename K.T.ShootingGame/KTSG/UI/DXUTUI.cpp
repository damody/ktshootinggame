#include "dxut/DXUT.h"
#include "DXUTUI.h"

CDXUTDialog* g_hud_test;
DXUTUI* g_ktsg_ui;

//void CALLBACK KTSGOnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void CALLBACK KTSGOnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
bool CALLBACK KTSGIsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
				    DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext );

HRESULT CALLBACK KTSGOnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
					 const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	g_ktsg_ui->m_DialogResourceManager.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) ;
	g_ktsg_ui->m_D3DSettingsDlg.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) ;
	return true;
}
DXUTUI::DXUTUI(void)
{
	// Disable gamma correction on this sample
 	DXUTSetIsInGammaCorrectMode( false );
// 
// 	//DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
// 	//DXUTSetCallbackMsgProc( MsgProc );
// 	DXUTSetCallbackKeyboard( KTSGOnKeyboard );
// //	DXUTSetCallbackFrameMove( OnFrameMove );
	g_ktsg_ui = this;
// 
 	DXUTSetCallbackD3D11DeviceAcceptable( KTSGIsD3D11DeviceAcceptable );

// 	DXUTSetCallbackD3D11DeviceCreated( OnD3D11CreateDevice );
 	DXUTSetCallbackD3D11SwapChainResized( KTSGOnD3D11ResizedSwapChain );
// 	DXUTSetCallbackD3D11FrameRender( OnD3D11FrameRender );
// 	DXUTSetCallbackD3D11SwapChainReleasing( OnD3D11ReleasingSwapChain );
// 	DXUTSetCallbackD3D11DeviceDestroyed( OnD3D11DestroyDevice );

	DXUTInit( true, true );                 // Use this line instead to try to create a hardware device

	DXUTSetCursorSettings( true, true );    // Show the cursor and clip it when in full screen
}

DXUTUI::~DXUTUI(void)
{
	DXUTGetExitCode();
}

void DXUTUI::SetWindow( HWND hWndFocus, bool bHandleMessages /*= TRUE*/ )
{
	DXUTSetWindow(hWndFocus, hWndFocus, hWndFocus, bHandleMessages);
}

void DXUTUI::CreateDevice( int winWidth, int winHeight)
{
	DXUTCreateDevice(D3D_FEATURE_LEVEL_11_0, true, winWidth, winHeight);
	m_DialogResourceManager.OnD3D11CreateDevice( DXUTGetD3D11Device(), DXUTGetD3D11DeviceContext() );
	m_D3DSettingsDlg.OnD3D11CreateDevice( DXUTGetD3D11Device() );
}

bool DXUTUI::InitDXUT()
{
	DXUTInit( true, true );
	m_D3DSettingsDlg.Init( &m_DialogResourceManager );
	m_HUD.Init( &m_DialogResourceManager );
	m_HUD.SetCallback( KTSGOnGUIEvent ); 
	m_HUD.AddButton( 1, L"TEST_BUTTON1", 0, 100, 170, 23 );
	m_HUD.AddStatic( 2, L"----", 5, 200, 108, 24 );
	g_hud_test = &m_HUD;
	m_HUD.SetBackgroundColors(D3DCOLOR_RGBA(0,255,0,100));
	m_HUD.EnableMouseInput(true);
	return true;
}

void DXUTUI::UpdataUI(float dt)
{
	//DXUTRender3DEnvironment();
	DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" );
	m_HUD.OnRender( dt );
	DXUT_EndPerfEvent();
}

void DXUTUI::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
	m_D3DSettingsDlg.MsgProc(hWnd, uMsg, wParam, lParam);
	m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
}

bool CALLBACK KTSGIsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	return true;
}

void CALLBACK KTSGOnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch( nControlID )
	{
	case 1:
		g_hud_test->GetStatic( 2 )->SetText( L"test success!" );
		break;
	}
}
