#include "State.h"
#include "Player.h"
void State::Enter()
{
	Owner = new Player;
}
