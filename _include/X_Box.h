#pragma once
#include "X_Math.h"

class X_Box 
{
public:
	H_Vector3 _VertexPos[8];
//aabb
	H_Vector3 _Max;
	H_Vector3 _Min;
//obb
	H_Vector3 _Center;
	H_Vector3 _Axis[3];
	float _Extent[3];
	H_Matrix _World;
public:
	void CreateBox(H_Vector3 axis[3], H_Vector3 cen , H_Matrix world);
};

