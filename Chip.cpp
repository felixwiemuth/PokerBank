/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Chip.h"

#include <iostream>

Chip::Chip()
{
    this->value = 0;
    this->name = "unnamed";
    this->amount = 0;
}

Chip::Chip(int value, std::string name, int amount)
{
    this->value = value;
    this->name = name;
    this->amount = amount;
}

bool Chip::reduce_amount(int n)
{
    if (amount < n)
        return false;
    amount -= n;
    return true;
}

void Chip::factor_value(double& factor)
{
    value = value*factor;
}

ostream& operator<<(ostream& os, const Chip& chip)
{
    os << "name=" << chip.name << " value=" << chip.value << " amount=" << chip.amount;
    return os;
}

int Chip::get_value()
{
    return value;
}

int Chip::get_amount()
{
    return amount;
}
