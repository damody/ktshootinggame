
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <d3dx11.h>

#include <dxerr.h>

#include <string>
#include <iostream>
#include   <time.h>
#include   <stdio.h>
#include <vector>
#include <sstream>
#include <tchar.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


//¥þ°ì¥¨¶°
#define ReleaseCOM(x) { if(x){ x->Release();x = 0; }}

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
		DXTraceW(_T(__FILE__), __LINE__, hr, L#x, TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 


