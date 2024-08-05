#include "WallClingState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "Player.h"
#include "Input.h"

void WallClingState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"WallCling.txt"));
	FallingSpeed = 15.f;
	Tag = WALLCLING;
	Owner->UpdateJumpSpeed();
	Owner->SetJumpState(true);
}

void WallClingState::Update()
{
	Owner->PlayAnimation();
	Owner->Falling(FallingSpeed);
	if (GameInput.GetKey('X') == KEY_PUSH)
	{
		Owner->SetAnimation(Owner->FindSprite(L"ShootWallCling.txt"));
		WaitTime = 0.0f;
	}
	else if (GameInput.GetKey('X') == KEY_FREE) 
	{
		//ChargeTime = 0.0f;
		//Charge = false;
		WaitTime += gSecondPerFrame;
		if (WaitTime > 0.2f) 
		{
			Owner->SetAnimation(Owner->FindSprite(L"WallCling.txt"));
			WaitTime = 0.0f;
		}
		/*if (ChargeState == CHARGEND) {
			SetSprite(FindSprite(L"ShootWallCling.txt"));
		}*/
	}
	if (GameInput.GetKey('C') == KEY_PUSH)
	{
		Owner->ChangeState(new JumpState);
		return;
	}
	if (Owner->GetIsGround())
	{
		Owner->ChangeState(new IdleState);
	}
}

void WallClingState::Exit()
{
	Owner->ResetAnimIndex();
	Owner->SetJumpState(false);
}
