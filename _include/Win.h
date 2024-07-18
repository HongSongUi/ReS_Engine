#pragma once
#include "X_Header.h"
#include "Device.h"
class X_Win
{
public:
	HINSTANCE _HInst;
	HWND _Hwnd;
	DWORD       m_csStyle;
	RECT WindowRt;
	RECT ClientRt;
	UINT ClientWidth;
	UINT ClientHeight;
	bool ResizeWindow = false;
	UINT width;
	UINT height;
public:
	bool				SetWindow(HINSTANCE hInstance, const WCHAR* Title, UINT width, UINT height);
	ATOM				MyRegisterClass();
	void				CenterWindow();
	BOOL                InitInstance(const WCHAR* Title, UINT width, UINT height);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	bool Run();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	X_Win();
};