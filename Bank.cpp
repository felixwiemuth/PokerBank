/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Bank.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>


using namespace std;

Bank::Bank()
{
    interest_buy = 0;
    interest_sell = 0;
    log.set_remote(&syslog);
    log.echo_off();
}

void Bank::buy_cui(vector<string> in)
{
    if (in.size() < 2)
    {
        syslog.err("You must at least specify a name and one type of chips to buy!");
        return;
    }
    buy_sell(true, in[0], str_to_chips(in.begin()+1, in.end()));
}

void Bank::sell_cui(vector<string> in)
{
    if (in.size() < 2)
    {
        syslog.err("You must at least specify a name and one type of chips to sell!");
        return;
    }
    buy_sell(false, in[0], str_to_chips(in.begin()+1, in.end()));
}

//void Bank::inflation(double factor)
//{
//
//}

void Bank::add_money(int amount)
{
    money += amount;
}

bool Bank::take_money(int amount)
{
    if (money < amount)
        return false;
    money -= amount;
    return true;
}

void Bank::add_chip(Chip chip)
{
    chips[chip.get_value()] = chip;
}

void Bank::remove_chip(int value)
{
    chips.erase(value);
}

int Bank::get_balance() {
    int ret = 0;
    for (map<int, Chip>::iterator it = chips.begin(); it != chips.end(); ++it) {
        ret += it->second.get_amount() * it->second.get_value();
    }
    return ret;
}

vector< pair<int, int> > Bank::str_to_chips(vector<string>::iterator first, vector<string>::iterator last)
{
    vector< pair<int, int> > ret(chips.size());
    //split words fo input in the two numbers: "4x50" --> n[0]=4 n[1] =50
    for (vector<string>::iterator it = first; it != last; ++it)
    {
        vector<string> n;
        boost::split(n, *it, [](const char c)->bool{return c == 'x';});
        if (n.size() != 2)
        {
            stringstream err;
            err << "'" << *it << "': Incorrect way to specify chip sort";
            syslog.err(err.str());
            continue;
        }
        int amount, value;
        try
        {
            amount = boost::lexical_cast<int>(n[0]);
            value = boost::lexical_cast<int>(n[1]);
        }
        catch (boost::bad_lexical_cast&)
        {
            stringstream err;
            err << "'" << *it << "': Chip amount and sort must be specified by numbers!";
            syslog.err(err.str());
            continue;
        }
        ret.push_back(pair<int, int>(amount, value));
    }
    return ret;
}

void Bank::buy_sell(bool buy, string name, vector< pair<int, int> > buychips)
{
    stringstream sstr;
    int sum = 0;
    sstr << name;
    if (buy)
        sstr << " bought";
    else
        sstr << " sold";

    for(vector< pair<int, int> >::iterator it = buychips.begin(); it != buychips.end(); ++it)
    {
        if (it->first == 0) //transfer no chips of this sort
            continue;
        //check if sort exists
        if (chips.find(it->second) == chips.end())
        {
            stringstream err;
            err << "Sort '" << it->second << "' does not exist!";
            syslog.err(err.str());
            continue;
        }
        if (buy)
        {
            //check if intended amount of chips available
            if (!chips[it->second].reduce_amount(it->first))
            {
                stringstream err;
                err << "Could not buy " << it->first << " chips of sort '" << it->second << "': only " << chips[it->second] << " chips available!";
                syslog.err(err.str());
                continue;
            }
        }
        else
            chips[it->second].increase_amount(it->first);

        //update log entry
        int add = it->first * it->second;
        sum += add;
        sstr << " " << it->first << "x" << it->second << " (" << add << ");";
    }
    //put log entry
    if (sum != 0)
    {
        if (buy)
        {
            sstr << "\nPlease pay: ";
            money += sum;
        }
        else
        {
            sstr << "\nYou get: ";
            money -= sum;
        }
        sstr << sum;
        log.add(sstr.str());
    }
    else
        syslog.err("No correct inputs - no chips transferred!");

}

