#pragma once

#include "dxut/DXUT.h"
#include "dxut/DXUTcamera.h"
#include "dxut/DXUTgui.h"
#include "dxut/DXUTsettingsdlg.h"

//#include "SDKmisc.h"
//#include "SDKMesh.h"
//#include <D3DX11tex.h>
#include <D3DX11.h>
//#include <D3DX11core.h>
//#include <D3DX11async.h>

struct CmdState
{
	int id;
	int state;
};

class DXUTUI
{
protected:
public:
	CDXUTDialogResourceManager  m_DialogResourceManager;    // Manager for shared resources of dialogs
	CD3DSettingsDlg             m_D3DSettingsDlg;           // Device settings dialog
	CDXUTDialog                 m_HUD;                      // Dialog for standard controls
	//CDXUTDialog                 m_SampleUI;                 // Dialog for sample specific controls
	//CDXUTTextHelper*            m_pTxtHelper;



	DXUTUI(void);
	~DXUTUI(void);

	void SetWindow(HWND hWndFocus, bool bHandleMessages = TRUE);
	void CreateDevice(int winWidth, int winHeight);
	ID3D11Device* GetDevice(){ return DXUTGetD3D11Device();}
	ID3D11DeviceContext* GetDeviceContext(){ return DXUTGetD3D11DeviceContext();}
	IDXGISwapChain* GetSwapChaine(){ return DXUTGetDXGISwapChain();}

	bool InitDXUT();

	void UpdataUI(float dt);
	void MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
