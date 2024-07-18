#pragma once
#include "X_BaseObject.h"
#include "Frustum.h"
class Cam3D:public X_BaseObject
{
public:
	H_Matrix _ViewMat;
	H_Matrix _ProjMat;
	H_Vector3 _Pos;
	H_Vector3 _Target = { 0.0f,0.0f,0.0f };
	H_Vector3 _Up = { 0,1,0 };
	float _Near;
	float _Far;
	float _Fov;
	float _Aspect;
	H_Vector3 _Right;
	H_Vector3 _Look;
	Frustum _Frustum;
	float     m_fYaw = 0.0f;
	float     m_fPitch = 0.0f;
	float     m_fRoll = 0.0f;
public:
	bool Init();
	virtual void CreateViewMatrix(H_Vector3 pos, H_Vector3 target, H_Vector3 up);
	virtual void CreateProjMatrix(float Near, float Far, float fov, float aspect);
	virtual void UpdateProjMatrix(float Aspect);
	virtual bool Frame();
	virtual void Update();
};

