#pragma once
#include "Vector3D.h"
class Sphere
{
public:
	Vector3D Center;
	float Radius;
public:
	void SetSphere(Vector3D cen, Vector3D BoxSize);
	bool Init() {};
	bool Render() {};
	bool Frame() {};
	bool Release() {};
public:
	Sphere();
	Sphere(Vector3D cen, Vector3D BoxSize);
};