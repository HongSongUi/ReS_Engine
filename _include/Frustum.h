#pragma once
#include "Matrix4x4.h"
#include "X_Math.h"
#include "X_Box.h"
using namespace X_BASIS_EX;

//평면의 법선 벡터는 안쪽을 바라보고 있음
enum X_POSITION {
	_BACK = 0,
	_FRONT,
	_ONPLANE,
	_SPANNING,
};
struct Plane {
	float a, b, c, d;
	H_Vector3 _PlaneVec;
	void Create(H_Vector3 v0, H_Vector3 v1, H_Vector3 v2) {
		H_Vector3 p1 = v1 - v0;
		H_Vector3 p2 = v2 - v0;
		H_Vector3 normal;
		D3DXVec3Cross(&normal, &p1, &p2);
		D3DXVec3Normalize(&normal, &normal);
		D3DXVec3Normalize(&normal, &normal);
		//normal.Normalize();
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -D3DXVec3Dot(&normal ,&v0);
		_PlaneVec.x = a;
		_PlaneVec.y = b;
		_PlaneVec.z = c;
	}
	void Create(H_Vector3 n, H_Vector3 v0) {
		D3DXVec3Normalize(&n, &n);
		a = n.x;
		b = n.y;
		c = n.z;
		d = -D3DXVec3Dot(&n ,&v0);
	}
};
class Frustum
{
	H_Matrix _ViewMat;
	H_Matrix _ProjMat;
public:
	H_Vector3 _Frustum[8];//필요한 정점 8개
	Plane _Plane[6];//절두체의 평면 6개
public:
	void CreateFrustum(H_Matrix* view, H_Matrix* proj);
	bool ClassifyPoint(H_Vector3 v);
	X_POSITION ClassifyBox(X_Box obb);
};

