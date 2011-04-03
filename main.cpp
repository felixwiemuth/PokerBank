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
    Chip chip1(50, "red", 200);
    bank.add_chip(chip1);
    string player1 = "Dieter";
    bank.add_player(player1);

    //add CUI-handlers
    cui["buy"].set(&bank, 0, &Bank::cui_buy).set_help("Syntax: [name] [n1]x[c1] [n2]x[c2] ... n = amount, c = chip value");
    cui["sell"].set(&bank, 0, &Bank::cui_sell);
    cui["add-money"].set(&bank, 0, &Bank::cui_add_money);
    cui["take-money"].set(&bank, 0, &Bank::cui_take_money);
    cui["set-interest-buy"].set(&bank, 0, &Bank::cui_set_interest_buy);
    cui["set-interest-sell"].set(&bank, 0, &Bank::cui_set_interest_sell);
    cui["add-players"].set(&bank, 0, &Bank::cui_add_players);
    cui["money"].set(&bank, &Bank::show_money);
    cui["chips"].set(&bank, &Bank::show_chips);
    cui["value"].set(&bank, &Bank::show_chip_value);
    cui["status"].set(&bank, &Bank::show_bank_status);
    // ||to add new copy:|| cui[""].set(&bank, &Bank::);
    cui[""].set(&bank, &Bank::exit_program);
    bank.set_interest_buy(0.1);
    bank.set_interest_sell(0.2);
    cui.run();


//    Bank bank2;
//    cout << "Banks balance: " << bank2.get_balance() << endl;
//    Chip c1(100, "MaanxD", 5);
//    cout << "Chip 1: " << c1;
    return 0;
}

