#ifndef D3DAPP_H
#define D3DAPP_H

#include <string>
#include <dwrite.h>
#include "Timer.h"

#include "ui/DXUTUI.h"

extern ID3D11Device* g_d3dDevice;

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	HINSTANCE getAppInst();
	HWND      getMainWnd();
	int run();
	virtual void initApp();
	virtual void onResize();// reset projection/etc
	virtual void updateScene(float dt);
	virtual void DrawScene(); 
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	void initMainWindow();
	void initDirect3D();
	
protected:

	HINSTANCE m_hAppInst;

	HWND      m_hMainWnd;
	bool      m_AppPaused;
	bool      m_Minimized;
	bool      m_Maximized;
	bool      m_Resizing;

	GameTimer m_Timer;

	std::wstring m_FrameStats;
 
	ID3D11Device*    m_d3dDevice;
	IDXGISwapChain*  m_SwapChain;
	ID3D11Texture2D* m_DepthStencilBuffer;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11DepthStencilView* m_DepthStencilView;
	D3D_FEATURE_LEVEL  m_FeatureLevelsSupported;
	ID3D11DeviceContext* m_DeviceContext;

	DXUTUI* m_DXUT_UI;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring m_MainWndCaption;
	D3D_DRIVER_TYPE m_d3dDriverType;
	D3DXCOLOR m_ClearColor;
	int mClientWidth;
	int mClientHeight;

};




#endif // D3DAPP_H