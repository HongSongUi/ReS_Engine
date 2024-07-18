#pragma once
#include "X_Header.h"
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")
class X_Writer
{
public:
	ID2D1Factory* _2DFactory;
	IDWriteFactory* _WriteFactory;
	ID2D1RenderTarget* _2DRenderTarget;
	IDWriteTextFormat* _TextFormat;
	ID2D1SolidColorBrush* _TextColor;
	std::wstring _DefaultText;
	RECT _ClientRt;
//	IDWriteTextLayout* _TextLayout;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	HRESULT Set(IDXGISurface1* Surface);
	bool Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0,0,0,1 });
	void SetClientRect(RECT rt);
	HRESULT DeleteDxResource();
	HRESULT CreateDxResource();
};

