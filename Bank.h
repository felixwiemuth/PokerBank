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
   The "cui_X" methods translate the users input to the corresponding "X" method
   and should be given to "CUI" as user interface.
   Additional methods without parameters can be given to "CUI" without anything special to care about.
*/

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
        void cui_buy(std::vector<std::string> in); //CUI api to buy chips -- form of 'in': "[name] [n1]x[c1] [n2]x[c2] ..." n = amount, c = chip value
        void cui_sell(std::vector<std::string> in); //CUI api to sell chips -- form of 'in': "[name] [n1]x[c1] [n2]x[c2] ..." n = amount, c = chip value
        void cui_add_money(std::vector<std::string> in);
        void cui_take_money(std::vector<std::string> in);
        /* --- methods --- */
        //void inflation(double factor);
        void set_interest_buy(double interest); //set 'interest_buy' to 'interest'
        void set_interest_sell(double interest);//set 'interest_sell' to 'interest'
        void add_money(int amount); //add 'amount' money to the bank
        bool take_money(int amount); //takes 'amount' money from the bank -- returns 'true' if enough money available to take 'amount'
        void add_player(std::string name); //add a new player with name 'name' to 'players'
        void add_chip(Chip chip);
        void remove_chip(int value); //removes chip sort with value 'value'
        std::vector<Player>::iterator check_player(std::string name); //returns iterator to player in 'players' if player with name 'name' existing
        int get_balance(); //return the value of all chips together
        //methods to show (log) status information
        void show_money();
        void show_chip_value();
        void show_chips();
        void show_bank_status(); //show every information if 'show_' methods together

        void exit_program(); //leave program
    private:
        std::vector< std::pair<int, int> > str_to_chips(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last); //convert input format of chips to internal format
        void buy_sell(bool buy, std::string name, std::vector< std::pair<int, int> > buychips); //player 'name' buys ('buy==true') or sells ('buy==false') 'sellchips[n]' chips of sort 'chips[n]'
        bool check_arguments(size_t is, size_t min, size_t max = -1); //check if 'is' is between 'min' and 'max' ('max='-1' means no max), if not displays error message and return 'false'
        template<class T> std::pair<bool, T> convert_s(std::string s); //converts 's' to type 'T' (numeric) and shows error on failure -- returns: first: sucess, second: resulting number

};

#endif	/* _BANK_H */

