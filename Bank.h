/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef _BANK_H_
#define	_BANK_H_

#include "Chip.h"

#include "lib/SimpleCUI/Cui.h"
#include "lib/SimpleLog/Log.h"
#include <vector>


class Bank
{
    public:
        Bank();
    private:
        std::vector<Chip> chips; //available chip sorts
        double interest_buy; //interest on buying chips from bank
        double interest_sell; //interest on selling chips to bank
    public:
        void sell(); //sells chips to player
        void inflation(double factor);
        void add_chip(Chip& chip);
        int get_balance(); //return the value of all chips
};

#endif	/* _BANK_H */

