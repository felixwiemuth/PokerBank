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
    cui["buy"].set(&bank, 0, &Bank::cui_buy).set_help("Syntax: [name] [n1]x[c1] [n2]x[c2] ... n = amount, c = chip value");
    cui["sell"].set(&bank, 0, &Bank::cui_sell);
    cui["add-money"].set(&bank, 0, &Bank::cui_add_money);
    cui["money"].set(&bank, &Bank::show_money);
    cui["chips"].set(&bank, &Bank::show_chips);
    cui["value"].set(&bank, &Bank::show_chip_value);
    cui["status"].set(&bank, &Bank::show_bank_status);
    // ||to add new copy:|| cui[""].set(&bank, &Bank::);
    cui["e"].set(&bank, &Bank::exit_program);
    bank.set_interest_buy(0.1);
    bank.set_interest_sell(0.2);
    cui.run();


//    Bank bank2;
//    cout << "Banks balance: " << bank2.get_balance() << endl;
//    Chip c1(100, "MaanxD", 5);
//    cout << "Chip 1: " << c1;
    return 0;
}

