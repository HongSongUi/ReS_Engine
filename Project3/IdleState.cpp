#include "IdleState.h"
#include "Input.h"
#include "Player.h"
void IdleState::Enter()
{
    State::Enter();
}

void IdleState::Update()
{
    if (Owner->GetIsGround() == false) {
        Owner->Falling();
    }
    else {
        if (GameInput.GetKey('X') == KEY_FREE) {
            if (Owner->GetChargeState() == CHARGEND) 
            {
                Owner->SetAnimation(Owner->FindSprite(L"ChargeShoot.txt"));
            }
            if (Owner->CheckAnimationIndex(1)) 
            {
                Owner->SetCurrentState();
            }
        }
        if (GameInput.GetKey('C') == KEY_PUSH)
        {
            Owner->ChangeState(new JumpState());
        }
        if (GameInput.GetKey(VK_DOWN) == KEY_HOLD) 
        {
            Owner->ChangeState(new CrouchState());
        }
        if (GameInput.GetKey(VK_LEFT) == KEY_HOLD) 
        {
            Owner->SetInverse(true);
            Owner->ChangeState(new WalkState());
        }
        if (GameInput.GetKey(VK_RIGHT) == KEY_HOLD)
        {
            Owner->SetInverse(false);
            Owner->ChangeState(new WalkState());
        }
        if (GameInput.GetKey('X') == KEY_PUSH) 
        {
            Owner->ChangeState(new ShootState());
        }
    }
}

void IdleState::Exit()
{
}
