#include "State.h"
#include "Player.h"
void State::Enter()
{
}

void State::SetOwner(Player* player)
{
	Owner = player;
}
