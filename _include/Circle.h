#pragma once
#include "Vector2D.h"
class Circle 
{
	
public:
	Vector2D Center;
	float Radius;
public:
	void SetCircle(Vector2D cen,Vector2D RtSize);
	bool Init() {};
	bool Render() {};
	bool Frame() {};
	bool Release() {};
public:
	Circle();
	Circle(Vector2D cen, Vector2D RtSize);
};

