#pragma once
#include "X_Header.h"
#include "X_Win.h"
enum KeyState {
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
class X_Input : public X_Singleton<X_Input>
{
private:
	DWORD dw_KeyState[256]; // mouse + Å°¹öÆ°
	HWND _Hwnd;
public:
	POINT _MousePos;
	POINT _PreMousePos;
	POINT _OffSet;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	DWORD GetKey(DWORD Key);
	void SetWinHwnd(HWND hwnd);

};
#define Input X_Input::GetInstance()

