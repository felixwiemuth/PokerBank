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
}

void Bank::buy_cui(vector<string> in)
{
    if (in.size() < 2)
    {
        //TODO ERR MSG
        return;
    }
    vector<int> buychips(chips.size());
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
    }
    buy(in[0], buychips);
}

void Bank::buy(string name, vector<int> buychips)
{
    stringstream sstr;
    int sum = 0;
    sstr << name + " bought";
    for(int i = 0; i < buychips.size(); i++)
    {
        if (buychips[i] == 0) //buy no chips of this sort
            continue;
        //check if intended amount of chips available
        if (!chips[i].reduce_amount(buychips[i]))
        {
            stringstream err;
            err << "Could not buy " << buychips[i] << " chips of sort '" << chips[i].get_value() << "': only " << chips[i].get_amount() << " chips available!";
            syslog.err(err.str());
            continue;
        }
        //update log entry
        int add = buychips[i]*chips[i].get_value();
        sum += add;
        sstr << " " << buychips[i] << "x" << chips[i].get_value() << " (" << add << ");";
    }
    //put log entry
    sstr << " sum: " << sum;
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

void Bank::add_chip(Chip& chip)
{
    chips.push_back(chip);
}

int Bank::get_balance() {
    int ret = 0;
    for (vector<Chip>::iterator it = chips.begin(); it != chips.end(); ++it) {
        ret += it->get_amount() * it->get_value();
    }
    return ret;
}

