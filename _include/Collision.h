#pragma once
#include "X_Rect.h"
/*#include "Circle.h"
#include "Box.h"
#include "Sphere.h"*/

/**
* 수정 필요
*/
class Collision
{
public:
	static bool RectToInRect(X_Rect& a, X_Rect& b);
	static bool RectToRect(X_Rect& a, X_Rect& b);
//	static bool CircleToCircle(Circle& a, Circle& b);
//public:
//	static bool BoxToInBox(Box& a, Box& b);
//	static bool BoxToBox(Box& a, Box& b);
//	static bool SphereToSphere(Sphere& a, Sphere& b);
};