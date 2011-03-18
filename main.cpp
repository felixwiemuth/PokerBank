/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

//#include <stdlib.h>
#include <iostream>

#include "Bank.h"

using namespace std;

/*
 *
 */
int main(/*int argc, char** argv*/)
{
    Cui<Bank> cui; //CUI as user interface
    Bank bank;
    //add CUI-handlers
    //cui["sell"].set(&bank, &Bank::sell);
    cui.run();


    Bank bank2;
    cout << "Banks balance: " << bank2.get_balance() << endl;
    Chip c1(100, "MaanxD", 5);
    cout << "Chip 1: " << c1;
    return 0;
}

