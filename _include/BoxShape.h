#pragma once
#include "Object3D.h"
#include "X_Box.h"
class BoxShape : public Object3D
{
public:
	H_Vector3 _ObbMax;
	H_Vector3 _ObbMin;
	H_Vector3 _Half;
	X_Box _Box;
public:
	void SetVertexList()override;
	void SetIndexList()override;
	void SetMatrix(H_Matrix* world, H_Matrix* view, H_Matrix* proj)override;

};

