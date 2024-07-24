#include "Player.h"

void Player::Falling()
{
	JumpForce = 0.5f;
	Postion.y += 1.0f * gSecondPerFrame * 9.8 * JumpForce * JumpForce;
}

bool Player::GetIsGround()
{
	return IsGround;
}

void Player::SetChargeState(ChargeState state)
{
	State = state;
}

ChargeState Player::GetChargeState()
{
	return State;
}
