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
        //TODO ERR MSG
        return;
    }
    vector< pair<int, int> > buychips(chips.size());
    //split words fo input in the two numbers: "4x50" --> n[0]=4 n[1] =50
    for (vector<string>::iterator it = in.begin()+1; it != in.end(); ++it)
    {
        vector<string> n;
        boost::split(n, *it, [](const char c)->bool{return c == 'x';});
        if (n.size() != 2)
        {
            //TODO ERR MSG
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
            //TODO ERR MSG
            continue;
        }
        //TODO add vals to buychips
        buychips.push_back(pair<int, int>(amount, value));
    }
    buy(in[0], buychips);
}

void Bank::buy(string name, vector< pair<int, int> > buychips)
{
    stringstream sstr;
    int sum = 0;
    sstr << name + " bought";
    for(vector< pair<int, int> >::iterator it = buychips.begin(); it != buychips.end(); ++it)
    {
        if (it->first == 0) //buy no chips of this sort
            continue;
        //check if sort exists
        if (chips.find(it->second) == chips.end())
        {
            stringstream err;
            err << "Sort '" << it->second << "' does not exist!";
            syslog.err(err.str());
            continue;
        }
        //check if intended amount of chips available
        if (!chips[it->second].reduce_amount(it->first))
        {
            stringstream err;
            err << "Could not buy " << it->first << " chips of sort '" << it->second << "': only " << chips[it->second] << " chips available!";
            syslog.err(err.str());
            continue;
        }
        //update log entry
        int add = it->first * it->second;
        sum += add;
        sstr << " " << it->first << "x" << it->second << " (" << add << ");";
    }
    //put log entry
    sstr << " resulting amount: " << sum;
    log.add(sstr.str());
}

void Bank::sell_cui(string in)
{

}

void Bank::sell(string name, vector<int> sellchips)
{
    cout << "Selling" << endl;
}

void Bank::inflation(double factor)
{

}

void Bank::add_chip(Chip chip)
{
    chips[chip.get_value()] = chip;
}

int Bank::get_balance() {
    int ret = 0;
    for (map<int, Chip>::iterator it = chips.begin(); it != chips.end(); ++it) {
        ret += it->second.get_amount() * it->second.get_value();
    }
    return ret;
}

