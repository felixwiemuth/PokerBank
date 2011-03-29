/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef _BANK_H_
#define	_BANK_H_

#include "Chip.h"
#include "Player.h"

#include "lib/SimpleCUI/Cui.h"
#include "lib/SimpleLog/Log.h"
#include <vector>
#include <map>

/* --- NOTE ---
   the "cui_X" methods translate the users input to the corresponding "X" method
   and should be given to "CUI" as user interface */

class Bank
{
    public:
        Bank();
    private:
        int money; //money belonging to the bank
        std::vector<Player> players; //TODO in methods below players can write #XXX instead of name, with "XXX" being their registred id or name
        Log syslog; //log to log everything
        Log log; //log to log bank activity
        std::map<int, Chip> chips; //available chip sorts
        double interest_buy; //interest on buying chips from bank
        double interest_sell; //interest on selling chips to bank
    public:
        /* --- CUI methods --- */
        void buy_cui(std::vector<std::string> in); //CUI api to buy chips -- form of 'in': "[name] [n1]x[c1] [n2]x[c2] ..." n = amount, c = chip value
        void sell_cui(std::vector<std::string> in); //CUI api to sell chips -- form of 'in': "[name] [n1]x[c1] [n2]x[c2] ..." n = amount, c = chip value
        /* --- methods --- */
        //void inflation(double factor);
        void add_money(int amount); //add 'amount' money to the bank
        bool take_money(int amount); //takes 'amount' money from the bank -- returns 'true' if enough money available to take 'amount'
        void add_chip(Chip chip);
        void remove_chip(int value); //removes chip sort with value 'value'
        int get_balance(); //return the value of all chips together
    private:
        std::vector< std::pair<int, int> > str_to_chips(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last); //convert input format of chips to internal format
        void buy_sell(bool buy, std::string name, std::vector< std::pair<int, int> > buychips); //player 'name' buys ('buy==true') or sells ('buy==false') 'sellchips[n]' chips of sort 'chips[n]'

};

#endif	/* _BANK_H */

