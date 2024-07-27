#include "InGame.h"
#include "Player.h"
#include "InGameBackGround.h"
#include "Wall.h"
#include "Camera2D.h"
bool InGame::Init()
{
    Character->Init();
    BackGround->Init();
    Block->Init();
    PlayerCam->SetData({ Character->WorldPos.x + 250,Character->WorldPos.y - 200 }, { 800,600 });
    BackGroundCam->SetData(PlayerCam->Position, { PlayerCam->CameraSize.x + (float)ClientRect.right ,  PlayerCam->CameraSize.y + (float)ClientRect.bottom });
    return true;
}

bool InGame::Frame()
{
    Character->Frame();
    BackGround->Frame();
    Block->Frame();
    return true;
}

bool InGame::Render()
{
    Character->Render();
    BackGround->Render();
    Block->Render();
    return true;
}

bool InGame::Release()
{
    Character->Release();
    BackGround->Release();
    Block->Release();
    return true;
}

void InGame::SetData(ID3D11Device* Device, ID3D11DeviceContext* Context, RECT ClientRt)
{
    ClientRect = ClientRt;
    Character = new Player;
    BackGround = new InGameBackGround;
    Block = new Wall;
    Character->SetData(Device, Context, ClientRt);
    BackGround->SetData(Device, Context, ClientRt);
    Block->SetData(Device, Context, ClientRt);
    Init();
}
