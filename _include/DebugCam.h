#pragma once
#include "Cam3D.h"
#include "X_Math.h"
class DebugCam : public Cam3D
{
public:
	virtual void CreateViewMatrix(H_Vector3 pos, H_Vector3 target, H_Vector3 up)override;
	virtual void CreateProjMatrix(float Near, float Far, float FoVy, float Aspect)override;
	virtual void UpdateProjMatrix(float Aspect)override;
	virtual bool Frame() override;
};

