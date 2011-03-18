/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Bank.h"

#include <iostream>

using namespace std;

Bank::Bank()
{
    interest_buy = 0;
    interest_sell = 0;
    log.set_remote(&syslog);
}

void Bank::sell()
{
    cout << "Selling" << endl;
}

void Bank::inflation(double factor)
{

}

void Bank::add_chip(Chip& chip)
{
    chips.push_back(chip);

}

int Bank::get_balance() {
    int ret = 0;
    for (vector<Chip>::iterator it = chips.begin(); it != chips.end(); ++it) {
        ret += it->get_amount() * it->get_value();
    }
    return ret;
}

