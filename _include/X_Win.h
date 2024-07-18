#pragma once
#include "X_Header.h"
#include "Device.h"
class X_Win
{
public:
	HINSTANCE _HInst;
	HWND _Hwnd;
	DWORD       m_csStyle;
	RECT _WindowRt;
	RECT _ClientRt;
	UINT _ClientWidth;
	UINT _ClientHeight;
	UINT _Width;
	UINT _Height;
	bool _ResizeWindow = false;
public:
	bool				SetWindow(HINSTANCE hInstance, const WCHAR* Title, UINT width, UINT height);
	ATOM				MyRegisterClass();
	void				CenterWindow();
	BOOL                InitInstance(const WCHAR* Title, UINT width, UINT height);
	void				SetWinhWnd(HWND hWnd);
	RECT				SetClientRtSize();
public:
	virtual bool Run();
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	X_Win();
};