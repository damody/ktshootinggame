#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#ifndef INPUT_H
#define INPUT_H
class Input
{
public:
	Input(const DWORD,const DWORD,const HINSTANCE,const HWND);
	~Input();
	void poll();
	const bool Keyinput(const char);
		bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();


	private:
	// Make private to prevent copying of members of this class.
	Input(const Input& rhs);
	Input& operator=(const Input& rhs);



private:
	IDirectInput8*       mDInput;
	IDirectInputDevice8* mKeyboard;
	char                 mKeyboardState[256]; 
		IDirectInputDevice8* mMouse;
	DIMOUSESTATE2        mMouseState;


};

extern Input* DirectInput;

#endif 