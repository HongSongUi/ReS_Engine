#pragma once
#include "X_Header.h"
#include "X_Win.h"
#include "Device.h"
#include "X_Timer.h"
#include "X_Input.h"
#include "X_Writer.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "DxState.h"
#include "X_BaseObject.h"
#include "RenderToTexture.h"
#include "DebugCam.h"
class GameCore
{
protected:
	ID3D11Device*			_Device = nullptr;
	ID3D11DeviceContext*	_Context = nullptr;
	X_BaseObject			_RenderTarget;
	X_Win					_Window;
	X_Writer				_Writer;
	X_Writer				_XVec;
	X_Writer				_YVec;
	X_Writer				_ZVec;
	std::wstring			_CamPos;
	std::wstring			_CamTarget;
	std::wstring			_CamUp;
	HWND					_Hwnd;
	RECT					_ClientRect;
	RenderToTexture			_RT;
	Device					_DX;
public:
	X_Writer				_CamData;
	DebugCam				_DbgCam;
	bool					_GameRun;
public:
	virtual bool Init();
	virtual bool Render();
	virtual bool Release();
	virtual bool Frame();
	virtual bool PreProcess();
	virtual bool PreFrame();
	virtual bool PostFrame();
	virtual bool PreRender();
	virtual bool PostRender();
	virtual bool PostProcess();
public:
	bool CoreInit();
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
	bool CorePreRender();
	bool CorePostRender();

public:
	bool					Run();
	bool					ToolRun();
	bool					SetWindow(HINSTANCE hInstance, const WCHAR* Title, UINT width, UINT height);
	void					ClearD3D11DeviceContext();
	void					UpdateCamString();
	void					SetHwnd(HWND hWnd);
	void					ReSizeWindow(UINT width, UINT height);
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
	HWND					GetWindowHwnd();
	RECT					GetClientRect();
};

