#ifndef D3DAPP_H
#define D3DAPP_H


#include "d3dutil.h"
#include <string>
#include <dwrite.h>
#include "Timer.h"

#include "../ui/DXUTUI.h"

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
	virtual void drawScene(); 
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	void initMainWindow();
	void initDirect3D();
	
protected:

	HINSTANCE mhAppInst;

	HWND      mhMainWnd;
	bool      mAppPaused;
	bool      mMinimized;
	bool      mMaximized;
	bool      mResizing;

	GameTimer mTimer;

	std::wstring mFrameStats;
 
	ID3D11Device*    md3dDevice;
	IDXGISwapChain*  mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D_FEATURE_LEVEL  FeatureLevelsSupported;
	ID3D11DeviceContext* mDeviceContext;

	DXUTUI* m_DXUT_UI;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	D3D_DRIVER_TYPE md3dDriverType;
	D3DXCOLOR mClearColor;
	int mClientWidth;
	int mClientHeight;

};




#endif // D3DAPP_H