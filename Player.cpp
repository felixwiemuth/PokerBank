/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Player.h"

int Player::nextid = 0;

Player::Player()
{
    init();
}

Player::Player(std::string name)
{
    this->name = name;
    init();
}

void Player::init()
{
    id = nextid;
    nextid++;
}
