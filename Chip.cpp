/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Chip.h"

#include <iostream>


using namespace std;


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

void Chip::increase_amount (int n)
{
    if (n > 0)
        amount += n;
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
    os << chip.name << "(" << chip.value << "): " << chip.amount;
    return os;
}

bool operator<(const Chip& c1, const Chip& c2)
{
    return (c1.value < c2.value);
}

const int& Chip::operator[](int i)
{
    return amount;
}

int Chip::get_value()
{
    return value;
}

string Chip::get_name()
{
    return name;
}

int Chip::get_amount()
{
    return amount;
}
