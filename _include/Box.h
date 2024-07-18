#pragma once

#include "Vector3D.h"
class Box 
{
public:
	Vector3D Min;
	Vector3D Max;
	Vector3D Size;
	Vector3D Center;
public:
	Box();
	Box(Vector3D min, Vector3D size);

public:
	void SetBox(Vector3D cen, Vector3D size);
	bool Init() {};
	bool Render() {};
	bool Frame() {};
	bool Release() {};
public:
	bool operator== (Box& a);
};

