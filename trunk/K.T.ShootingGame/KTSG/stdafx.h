#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <winuser.h>
#include <d3dx11.h>

#include <dxerr.h>
#include <cassert>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <sstream>
#include <tchar.h>

//¥þ°ì¥¨¶°
#define ReleaseCOM(x) { if(x){ x->Release();x = 0; }}

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
		DXTrace(__FILE__, __LINE__, hr, _T(#x), TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 


