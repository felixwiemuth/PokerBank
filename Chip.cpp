/*
 * File:   Chip.cpp
 * Author: Felix
 *
 * Created on 7. Februar 2011, 15:11
 */

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

void Chip::factor_value(double& factor)
{
    value = value*factor;
}

//void Chip::print()
//{
//
//}

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
