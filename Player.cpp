/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Player.h"

#include <sstream>
#include <iomanip>

using namespace std;

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

string Player::tostr() const
{
    stringstream sstr;
    sstr << name << " (ID" << setfill('0') << setw(2) << id << ")";
    return sstr.str();
}

ostream& operator<<(ostream& os, const Player& p)
{
    os << p.tostr();
    return os;
}

void Player::init()
{
    id = nextid;
    nextid++;
}
