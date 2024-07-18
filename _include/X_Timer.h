#pragma once
#include "X_Header.h"
#pragma comment(lib, "winmm.lib") 
class X_Timer : public X_Singleton<X_Timer>
{
public:
	float _GameTimer = 0.0f;
	float _ElapseTimer = 10.0f;
	UINT _FPS = 0;
	std::wstring _szTimer;
private:
	DWORD _BeforeTime;
	UINT _FPSCounter = 0;
	float _FPSTimer = 0.0f;
public:
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
};

#define Timer X_Timer::GetInstance()