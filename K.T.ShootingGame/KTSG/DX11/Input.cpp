#include "input.h"
#include "headfile.h"

Input* DirectInput = 0;

Input::Input(const DWORD key,const DWORD mouseCoopFlags,const HINSTANCE appInst,const HWND hwnd)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

	//step1 create device
	HR(DirectInput8Create(appInst,DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&mDInput, 0));
	HR(mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0));
	//step2 set data format
	HR(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
	//step3 set cooperatve level
	HR(mKeyboard->SetCooperativeLevel(hwnd,key));
	//step4 acquire devic
	HR(mKeyboard->Acquire());


	
	HR(mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0));
	HR(mMouse->SetDataFormat(&c_dfDIMouse2));
	HR(mMouse->SetCooperativeLevel(hwnd, mouseCoopFlags));
	HR(mMouse->Acquire());
	

}
Input::~Input()
{
	ReleaseCOM(mDInput);
	mKeyboard->Unacquire();
		mMouse->Unacquire();
	ReleaseCOM(mKeyboard);
	ReleaseCOM(mMouse);


}
void Input::poll()
{
	  HRESULT hr = mKeyboard->GetDeviceState(sizeof(mKeyboardState),
                                            (void**)&mKeyboardState);
      if( FAILED(hr) )
      {
            // Keyboard lost, zero out keyboard data structure.
            ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

            // Try to acquire for next time we poll.
            hr = mKeyboard->Acquire();

      }

	  // Poll mouse.
	hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&mMouseState); 
	if( FAILED(hr) )
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&mMouseState, sizeof(mMouseState));

		// Try to acquire for next time we poll.
		hr = mMouse->Acquire(); 
	}


}
const bool Input::Keyinput(const char key)
{
	 return (mKeyboardState[key] & 0x80) != 0;
}
bool Input::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

float Input::mouseDX()
{
	return (float)mMouseState.lX;
}

float Input::mouseDY()
{
	return (float)mMouseState.lY;
}

float Input::mouseDZ()
{
	return (float)mMouseState.lZ;
}