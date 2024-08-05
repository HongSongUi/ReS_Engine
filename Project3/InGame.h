#pragma once
#include "Scene.h"

class InGame : public Scene
{
	class Player* Character;
	class InGameBackGround* BackGround;
	class Wall* Block;
	class Camera2D* PlayerCam;
	class Camera2D* BackGroundCam;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	virtual void SetData(ID3D11Device* Device, ID3D11DeviceContext* Context, RECT ClientRt)override;
	void UpdateCamera();
	void CheckPlayerCollision();
	void CameraPositionAdjust();
};

