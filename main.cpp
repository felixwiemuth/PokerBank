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
    cui["buy"].set(&bank, 0, &Bank::cui_buy).set_help("Buy chips from bank. Syntax: [name] [n1]x[c1] [n2]x[c2] ... n = amount, c = chip value");
    cui["sell"].set(&bank, 0, &Bank::cui_sell).set_help("Sell chips to bank. Syntax: [name] [n1]x[c1] [n2]x[c2] ... n = amount, c = chip value");
    cui["add-money"].set(&bank, 0, &Bank::cui_add_money).set_help("Add money to bank. Syntax: [amount] [message]");
    cui["take-money"].set(&bank, 0, &Bank::cui_take_money).set_help("Take money from bank. Syntax: [amount] [message]");
    cui["set-interest-buy"].set(&bank, 0, &Bank::cui_set_interest_buy).set_help("Set interest on purchase of chips. Syntax: [percent interest e.g. 2 or 0.5]");
    cui["set-interest-sell"].set(&bank, 0, &Bank::cui_set_interest_sell).set_help("Set interest on selling of chips. Syntax: [percent interest e.g. 2 or 0.5]");
    cui["add-players"].set(&bank, 0, &Bank::cui_add_players).set_help("Register new players to bank. Syntax: [name1] [name2] ...");
    cui["remove-players"].set(&bank, 0, &Bank::cui_remove_players).set_help("Remove registered players from bank. Syntax: [name/id 1] [name/id 2] ...");
    cui["add-chips"].set(&bank, 0, &Bank::cui_add_chip_sorts).set_help("Register new (or overwrite old) chip sorts. Syntax: [amount1] [name1] [value1] [amount2] [name2] [value2] ...");
    cui["remove-chips"].set(&bank, 0, &Bank::cui_remove_chip_sorts).set_help("Remove chip sorts. Syntax: [amount1] [name1] [value1] [amount2] [name2] [value2] ...");
    cui["chg-amount"].set(&bank, 0, &Bank::cui_change_chip_amount).set_help("Change amount of chips of different sorts. Syntax: [diff1]x[value1] [diff2]x[value2] ...");
    cui["log-set"].set(&bank, 0, &Bank::cui_set_log).set_help("");
    cui["money"].set(&bank, &Bank::show_money).set_help("Display money of bank.");
    cui["interest"].set(&bank, &Bank::show_interest).set_help("Display interest on buying/selling.");
    cui["chips"].set(&bank, &Bank::show_chips).set_help("Display all chips.");
    cui["value"].set(&bank, &Bank::show_chip_value).set_help("Display the value of all chips together.");
    cui["status"].set(&bank, &Bank::show_bank_status).set_help("Display status of bank.");
    cui["players"].set(&bank, &Bank::show_players).set_help("Display players registered to bank.");
    // ||to add new copy:|| cui[""].set(&bank, &Bank::);
    cui[""].set(&bank, &Bank::exit_program);
    bank.set_interest_buy(0.0075);
    bank.set_interest_sell(0.075);
    cui.run();


//    Bank bank2;
//    cout << "Banks balance: " << bank2.get_balance() << endl;
//    Chip c1(100, "MaanxD", 5);
//    cout << "Chip 1: " << c1;
    return 0;
}

