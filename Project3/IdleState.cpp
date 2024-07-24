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
            if (Owner->GetChargeState() == CHARGEND) {
                //SetSprite(FindSprite(L"ChargeShoot.txt"));
            }
            if (_Index >= _Play.size() - 1) {
               // SetSprite(_CurrIdle);
            }
        }
        if (GameInput.GetKey('C') == KEY_PUSH) {
           // ChangeState(new JumpState());
        }
        if (GameInput.GetKey(VK_DOWN) == KEY_HOLD) {
          //  ChangeState(new CrouchState());
        }
        if (GameInput.GetKey(VK_LEFT) == KEY_HOLD) {
           // _Inverse = true;
           // ChangeState(new WalkState());
        }
        if (GameInput.GetKey(VK_RIGHT) == KEY_HOLD) {
           // _Inverse = false;
           // ChangeState(new WalkState());
        }
        if (GameInput.GetKey('X') == KEY_PUSH) {
           // ChangeState(new ShootState());
        }
    }
}

void IdleState::Exit()
{
}
