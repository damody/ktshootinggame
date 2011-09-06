#pragma once

#include <vector>

#include "../Lua/LuaCell.h"
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

enum CommandType
{
	COMMAND_BUTTON=1,
	COMMAND_TEXT,
	COMMAND_COMBO_BOX
};

struct CmdState
{
	int id;
	int state;		//-1=no event
};
// 		--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標, 
// 			--		cw=控制項寬度, ch=控制項長度}
struct KTSGCommand
{
	int id;			//command id
	char text[128];		//command static text
	CommandType type;	//type
	float px,py;		//x,y coordinate
	int w,h;		//command width, height
};

class UIDialog
{
public:
	int id;
	bool isopen;
	UIDialog(){m_uidig=NULL; isopen=true;}
	~UIDialog(){if (m_uidig) delete m_uidig;}
	std::vector<KTSGCommand>	m_comset;
	CDXUTDialog*	m_uidig;
	void init(){m_uidig = new CDXUTDialog;}
	void close();
	void open();
	void updata(float dt);
};

class DXUTUI
{
protected:
	LuaCell		m_Luacell;
public:
	int	m_NextUIid;
	std::vector<CmdState>*		m_CmdStateSet;
	std::vector<UIDialog>		m_DialogSet;
	CDXUTDialogResourceManager	m_DialogResourceManager;    // Manager for shared resources of dialogs
	CD3DSettingsDlg			m_D3DSettingsDlg;           // Device settings dialog
	//CDXUTDialog                 m_SampleUI;                 // Dialog for sample specific controls
	//CDXUTTextHelper*            m_pTxtHelper;



	DXUTUI(void);
	~DXUTUI(void);

	//init fun
	void SetWindow(HWND hWndFocus, bool bHandleMessages = TRUE);
	void CreateDevice(int winWidth, int winHeight);
	ID3D11Device* GetDevice(){ return DXUTGetD3D11Device();}
	ID3D11DeviceContext* GetDeviceContext(){ return DXUTGetD3D11DeviceContext();}
	IDXGISwapChain* GetSwapChaine(){ return DXUTGetDXGISwapChain();}
	bool InitDXUT();

	void UpdataUI(float dt);
	void MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void LoadUI(const char* path);
	void OpenUI(int id);
	void CloseUI(int id);

	void AddNewUI(const char* path);
	void AddNewUI(const wchar_t* path);
};
