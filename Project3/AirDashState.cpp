#include "AirDashState.h"
#include "JumpState.h"
#include "Player.h"
void AirDashState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Dash.txt"));
	Tag = AIRDASH;
	DashTime = 0.55f;
}

void AirDashState::Update()
{
	Owner->PlayAnimation();
	DashTime -= gSecondPerFrame;
	if (!Owner->GetLeftWallState() && !Owner->GetRightWallState())
	{
		Owner->PlayerDash(500.f);
	}
	if (DashTime < 0.f)
	{
		Owner->ChangeState(new JumpState);
	}
}

void AirDashState::Exit()
{
	Owner->SetFallingAnim();
}
