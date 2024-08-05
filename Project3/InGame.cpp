#include "InGame.h"
#include "Player.h"
#include "InGameBackGround.h"
#include "Wall.h"
#include "Camera2D.h"
//#include "Collision.h"
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
    CheckPlayerCollision();
    BackGround->CameraSet(PlayerCam->Position, BackGroundCam->CameraSize);
    Character->Frame();
    Character->CameraSet(PlayerCam->Position, PlayerCam->CameraSize);
    Block->CameraSet(PlayerCam->Position, PlayerCam->CameraSize);
    UpdateCamera();
    CameraPositionAdjust();
    return true;
}

bool InGame::Render()
{
    BackGround->Render();
    Block->MaskRender();
    Character->MaskRender();
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
    PlayerCam = new Camera2D;
    BackGroundCam = new Camera2D;
    Character->SetData(Device, Context, ClientRt);
    BackGround->SetData(Device, Context, ClientRt);
    Block->SetData(Device, Context, ClientRt);
    Init();
}

void InGame::UpdateCamera()
{
    PlayerCam->SetData({ Character->WorldPos.x + 250  ,Character->WorldPos.y - 200 }, PlayerCam->CameraSize);
    BackGroundCam->SetData(PlayerCam->Position, BackGroundCam->CameraSize);
}

void InGame::CheckPlayerCollision()
{
    
    Character->SetLeftWallState(Collision::RectToRect(Character->ObjectRect, Block->LeftWall));

    Character->SetRightWallState(Collision::RectToRect(Character->ObjectRect, Block->RightWall));

    Character->SetGroundState(Collision::RectToRect(Character->ObjectRect, Block->Ground));
}

void InGame::CameraPositionAdjust()
{
    if (PlayerCam->Max.x >= BackGround->ObjectRect.Max.x)
    {
        PlayerCam->Position.x = PlayerCam->Position.x - (PlayerCam->Max.x - BackGround->ObjectRect.Max.x);   
    }
    else if (PlayerCam->Min.x <= BackGround->ObjectRect.Min.x)
    {
        PlayerCam->Position.x = PlayerCam->Position.x + (BackGround->ObjectRect.Min.x - PlayerCam->Min.x);
    }
    if (PlayerCam->Min.y <= BackGround->ObjectRect.Min.y)
    {
        PlayerCam->Position.y = PlayerCam->Position.y + (BackGround->ObjectRect.Min.y - PlayerCam->Min.y);
    }
    else if (PlayerCam->Max.y >= BackGround->ObjectRect.Max.y)
    {
        PlayerCam->Position.y = PlayerCam->Position.y - (PlayerCam->Max.y - BackGround->ObjectRect.Max.y);
    }
    PlayerCam->SetData(PlayerCam->Position, PlayerCam->CameraSize);
}
