#include "CrouchState.h"
#include "Player.h"
#include "Input.h"
#include "IdleState.h"
void CrouchState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Crouch.txt"));
	Tag = CROUCH;
}

void CrouchState::Update()
{
	Owner->PlayAnimation();
	if (GameInput.GetKey('X') == KEY_PUSH) 
	{
		WaitTime = 0.f;
		Owner->SetAnimation(Owner->FindSprite(L"CrouchShoot.txt"));
	}
	else if (GameInput.GetKey('X') == KEY_FREE) 
	{
		WaitTime += gSecondPerFrame;
		if (WaitTime > 0.1f) 
		{
			Owner->SetAnimation(Owner->FindSprite(L"Crouch.txt"));
		}
		//ChargeTime = 0.0f;
		//Charge = false;
		//WaitTime += gSecondPerFrame;
		//if (ChargeState == CHARGEND) {
			//SetSprite(FindSprite(L"CrouchCharge.txt"));
		//}
		//if (WaitTime > 0.1f) {
		
		//	WaitTime = 0.0f;
		//}
	}
	if (GameInput.GetKey(VK_DOWN) == KEY_FREE) 
	{
		Owner->ChangeState(new IdleState());
	}

}

void CrouchState::Exit()
{
	Owner->ResetAnimIndex();
}
