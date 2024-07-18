#pragma once
#include "X_BaseObject.h"
#include "ObjectDirLine.h"
#include "X_Math.h"
class Object3D :public X_BaseObject
{
public:
	H_Vector3 _Pos;
	H_Vector3 Axis[3];
	
	H_Vector3 _Max;
	H_Vector3 _Min;

	H_Vector3 PreAxis[3];
	ObjectDirLine* _DirLine;
public:
	Object3D() { SetListSize(); };
	virtual ~Object3D() {};
public:
	virtual void SetMatrix(H_Matrix* world, H_Matrix* view, H_Matrix* proj)override;
	virtual void SetListSize() override;
	virtual bool Render()override;
	virtual void SetDirLine();
	virtual bool Release()override;
};

