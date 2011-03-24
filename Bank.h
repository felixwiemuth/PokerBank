/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef _BANK_H_
#define	_BANK_H_

#include "Chip.h"
#include "Player.h"

#include "lib/SimpleCUI/Cui.h"
#include "lib/SimpleLog/Log.h"
#include <vector>

//note: every public method should be given to CUI //TODO or mark methods that should be given to CUI -- marked with "***CUI***"
//      the "cui_X" methods translate the users input to the corresponding "X" method


class Bank
{
    public:
        Bank();
    private:
        vector<Player> players; //TODO in methods below players can write #XXX instead of name, with "XXX" being their registred id or name
        Log syslog; //log to log everything
        Log log; //log to log bank activity
        std::vector<Chip> chips; //available chip sorts
        double interest_buy; //interest on buying chips from bank
        double interest_sell; //interest on selling chips to bank
    public:
        void buy_cui(std::vector<std::string> in); //from of 'in': "[name] [n1]x[c1] [n2]x[c2] ..." n = amount, c = chip value
        void buy(std::string name, std::vector<int> buychips); //player 'name' buys 'buychips[n]' chips of sort 'chips[n]'
        void sell_cui(std::string in);
        void sell(std::string name, std::vector<int> buychips); //player 'name' sells 'sellchips[n]' chips of sort 'chips[n]'
        void inflation(double factor);
        void add_chip(Chip& chip);
        int get_balance(); //return the value of all chips
    private:

};

#endif	/* _BANK_H */

