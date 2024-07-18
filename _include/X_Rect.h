#pragma once
#include "X_Math.h"
#define X_Epsilon 0.0001f
class X_Rect
{
public:
	H_Vector2 Center;
	H_Vector2 Min;
	H_Vector2 Max;
	H_Vector2 Size;
public:
	X_Rect();
	X_Rect(H_Vector2 cen, H_Vector2 size);
	X_Rect(float left, float top, float right, float bottom);
public:
	void SetRect(H_Vector2 cen,H_Vector2 size);
	void SetRect(float left, float top, float right, float bottom);
	bool Init() {};
	bool Render();
	bool Frame() {};
	bool Release() {};
public:
	bool operator== (X_Rect& a);
};

