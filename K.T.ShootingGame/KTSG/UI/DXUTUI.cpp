#include "dxut/DXUT.h"
#include "DXUTUI.h"
#include "../ConvStr.h"


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
	m_CmdStateSet = NULL;
	g_ktsg_ui = this;
	m_NextUIid = 1;

	// Disable gamma correction on this sample
	DXUTSetIsInGammaCorrectMode( false );
	DXUTSetCallbackD3D11SwapChainResized( KTSGOnD3D11ResizedSwapChain );
	DXUTSetCallbackD3D11DeviceAcceptable( KTSGIsD3D11DeviceAcceptable );
// 	//DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
// 	//DXUTSetCallbackMsgProc( MsgProc );
// 	DXUTSetCallbackKeyboard( KTSGOnKeyboard );
// //	DXUTSetCallbackFrameMove( OnFrameMove );

// 	DXUTSetCallbackD3D11DeviceCreated( OnD3D11CreateDevice );
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
	LoadUI("UI/UI.lua");

	return true;
}

void DXUTUI::UpdataUI(float dt)
{
	//DXUTRender3DEnvironment();
	DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" );
	for (int i=0; i<m_DialogSet.size(); i++)
		m_DialogSet[i].updata(dt);
	DXUT_EndPerfEvent();
}

void DXUTUI::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
	m_D3DSettingsDlg.MsgProc(hWnd, uMsg, wParam, lParam);
	for (int i=0; i<m_DialogSet.size(); i++)
		m_DialogSet[i].m_uidig->MsgProc(hWnd, uMsg, wParam, lParam);
}

// void DXUTUI::AddNewUI( const char* path )
// {
// 	return 1;
// }
// 
// void DXUTUI::AddNewUI( const wchar_t* path )
// {
// 	return 1;
// }

void DXUTUI::LoadUI( const char* path )
{
	char luar[128];
	int ui_num, cmd_num, combo_num;
	int cid;
	const char* ctext;
	int ctype;
	float cpx,cpy;
	int cw,ch;
	wchar_t* wtext = new wchar_t[128];
	CDXUTComboBox *combo;
	CmdState newstate;

	m_Luacell.InputLuaFile(path);
	ui_num = m_Luacell.getLua<int>("uinum");
	if (ui_num<1)
		return;

	CDXUTDialog* m_uidig = new CDXUTDialog;

	m_DialogSet.resize(ui_num);
	for (int i=0; i<ui_num; i++)
	{
		sprintf_s(luar, 128, "ui%d/cmdnum", i+1);
		cmd_num = m_Luacell.getLua<int>(luar);
		if (cmd_num<0)
			cmd_num = 0;
		m_DialogSet[i].init();
		m_DialogSet[i].m_uidig->Init( &m_DialogResourceManager );
		m_DialogSet[i].m_uidig->SetCallback( KTSGOnGUIEvent ); 
		m_DialogSet[i].m_comset.resize(cmd_num);
		for (int j=0; j<cmd_num; j++)
		{
			sprintf_s(luar, 128, "ui%d/cmd%d/cid", i+1, j+1);
			cid = m_Luacell.getLua<int>(luar);
			m_DialogSet[i].m_comset[j].id = cid;

			sprintf_s(luar, 128, "ui%d/cmd%d/ctext", i+1, j+1);
			ctext = m_Luacell.getLua<const char*>(luar);
			strcpy_s(m_DialogSet[i].m_comset[j].text, 128, ctext);

			sprintf_s(luar, 128, "ui%d/cmd%d/ctype", i+1, j+1);
			ctype = m_Luacell.getLua<int>(luar);
			m_DialogSet[i].m_comset[j].type = (CommandType)ctype;

			sprintf_s(luar, 128, "ui%d/cmd%d/cpx", i+1, j+1);
			cpx = (float)m_Luacell.getLua<double>(luar);
			m_DialogSet[i].m_comset[j].px = cpx;

			sprintf_s(luar, 128, "ui%d/cmd%d/cpy", i+1, j+1);
			cpy = (float)m_Luacell.getLua<double>(luar);
			m_DialogSet[i].m_comset[j].py = cpy;

			sprintf_s(luar, 128, "ui%d/cmd%d/cw", i+1, j+1);
			cw = m_Luacell.getLua<int>(luar);
			m_DialogSet[i].m_comset[j].w = cw;

			sprintf_s(luar, 128, "ui%d/cmd%d/ch", i+1, j+1);
			ch = m_Luacell.getLua<int>(luar);
			m_DialogSet[i].m_comset[j].h = ch;

			ConvStr::CharToWchar(wtext, ctext);
			switch(ctype)
			{
			case COMMAND_BUTTON:
				m_DialogSet[i].m_uidig->AddButton(cid, wtext, cpx, cpy, cw, ch);
				break;
			case COMMAND_TEXT:
				m_DialogSet[i].m_uidig->AddStatic(cid, wtext, cpx, cpy, cw, ch);
				break;
			case COMMAND_COMBO_BOX:
				m_DialogSet[i].m_uidig->AddComboBox(cid, cpx,cpy, cw, ch, 0, true, &combo);
				sprintf_s(luar, 128, "ui%d/cmd%d/itemnum", i+1, j+1);
				combo_num = m_Luacell.getLua<int>(luar);
				
				if (combo)
				{
					combo->SetSelectedByIndex( 0 );
					for (int k=0; k<combo_num; k++)
					{
						sprintf_s(luar, 128, "ui%d/cmd%d/item%d", i+1, j+1, k+1);
						ctext = m_Luacell.getLua<const char*>(luar);
						ConvStr::CharToWchar(wtext, ctext);
						combo->AddItem(wtext, NULL);						
					}
					combo->SetSelectedByIndex( 0 );
				}
				break;
			}
		}
		m_DialogSet[i].id = m_NextUIid;
		m_NextUIid++;
		m_DialogSet[i].close();
	}
	OpenUI(1);
	delete []wtext;
}

void DXUTUI::OpenUI( int id )
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].id==id)
		{
			m_DialogSet[i].open();
			return;
		}
	}
}

void DXUTUI::CloseUI( int id )
{
	for (int i=0; i<m_DialogSet.size(); i++)
	{
		if (m_DialogSet[i].id==id)
		{
			m_DialogSet[i].close();
			return;
		}
	}
}

bool CALLBACK KTSGIsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	return true;
}

void CALLBACK KTSGOnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{

}

void UIDialog::close()
{
	m_uidig->SetVisible(false);
	isopen = false;
}

void UIDialog::open()
{
	m_uidig->SetVisible(true);
	isopen = true;
}

void UIDialog::updata(float dt)
{
	if (isopen)
		m_uidig->OnRender(dt);
}
