#include "Player.h"

Player::Player ()
{
}

Player::Player (int _type)
{
  type = _type;
}

bool Player::isHuman()
{
  return type == HUMAN;
}
