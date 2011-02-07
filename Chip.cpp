/* 
 * File:   Chip.cpp
 * Author: Felix
 * 
 * Created on 7. Februar 2011, 15:11
 */

#include "Chip.h"

Chip::Chip() {
    this->value = 0;
    this->name = "unnamed";
    this->amount = 0;
}

Chip::Chip(int value, std::string name, int amount) {
    this->value = value;
    this->name = name;
    this->amount = amount;
}

void Chip::print() {

}

