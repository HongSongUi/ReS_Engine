#pragma once
#include "BaseObject.h"
class Object2D : public BaseObject
{
private:
	Vector2 NdcPos;
	Vector2 NdcSize;
public:
	float Mass;
	float Speed;
	bool Inverse = true;
public:
	Rect TextureRt;
	Rect UvRect;
	Rect ShowRect;
	POINT TextureSize;
	Rect ObjectRect;
	Vector2 Dir;
	Vector2 Size;
	Vector2 WorldPos;
	Vector2 CamPos;
	Vector2 CamSize;
public:
	Object2D() {
		SetPhysics();
	}
	virtual ~Object2D() {};
public:
	virtual bool Frame()override;
	virtual void SetVertexList()override ;
	void UpdateVertexList();
	void SetPosition(Vector2 pos);
	void ScreenToNdc();
	void ScreenToView(Vector2 CamPos, Vector2 CamSize);
	void SetPhysics() ;
	void SetRect(Rect rt);
};

