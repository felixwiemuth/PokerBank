/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

//#include <stdlib.h>
#include <iostream>

#include "Bank.h"

using namespace std;


int main(/*int argc, char** argv*/)
{
    Cui<Bank> cui; //CUI as user interface
    Bank bank;
    bank.add_chip(Chip(50, "red", 200));

    //add CUI-handlers
    cui["buy"].set(&bank, 0, &Bank::buy_cui);
    cui["sell"].set(&bank, 0, &Bank::sell_cui);
    cui.run();


//    Bank bank2;
//    cout << "Banks balance: " << bank2.get_balance() << endl;
//    Chip c1(100, "MaanxD", 5);
//    cout << "Chip 1: " << c1;
    return 0;
}

