/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef _BANK_H_
#define	_BANK_H_

#include "Chip.h"

#include <felixwiemuth-CUI-v1.0.1-0-ga9cb660/Cui.h>
#include <vector>


class Bank
{
    public:
        Bank();
    private:
        Cui<Bank> cui;
        std::vector<Chip> chips;
        double interest;
    public:
        void run(); //passes control to 'cui'
        void sell(); //sells chips to player
        void inflation(double factor);
        void add_chip(Chip& chip);
        int get_balance(); //return the value of all chips
};

#endif	/* _BANK_H */

