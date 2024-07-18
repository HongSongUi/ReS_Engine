#pragma once
#include "X_BaseObject.h"
class Object2D : public X_BaseObject
{
private:
	//Vector2D _NdcPos;
	//Vector2D _NdcSize;
public:
	X_Rect _TextureRt;
	X_Rect _UvRect;
	X_Rect _ShowRect;
	POINT _TextureSize;
public:
	X_Rect _ObjectRt;
	//Circle _ObjectCir;
	//Vector2D _Dir;
	//Vector2D _Size;
public:
//	Vector2D _WorldPos;
	//Vector2D _CamPos;
	//Vector2D _CamSize;
public:
	/*Object2D() {
		SetPhysics();
	}*/
	virtual ~Object2D() {};
public:
	/*virtual bool Frame()override;
	virtual void SetVertexList()override ;
	void SetPosition(Vector2D pos) override;
	void ScreenToNdc();
	void ScreenToView(Vector2D CamPos, Vector2D CamSize);
	virtual void SetPhysics() override ;
	void SetRect(Rect rt) ;*/
};

