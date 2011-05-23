/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Bank.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <algorithm>


using namespace std;

Bank::Bank()
{
    interest_buy = 0;
    interest_sell = 0;
    money = 0;
    chips_players = 0;
    log.set_remote(&syslog);
    log.echo_off();
    syslog.set_file_name("syslog");
    log.set_autosave(2); //save on destruction
    syslog.set_autosave(2); //save on destruction
    syslog.log_info();
    syslog.add("Welcome to PokerBank!");
}

void Bank::cui_buy(vector<string> in)
{
    if (!check_arguments(in.size(), 2))
        return;
    buy_sell(true, in[0], str_to_chips(in.begin()+1, in.end()));
}

void Bank::cui_sell(vector<string> in)
{
    if (!check_arguments(in.size(), 2))
        return;
    buy_sell(false, in[0], str_to_chips(in.begin()+1, in.end()));
}

void Bank::cui_add_money(vector<string> in)
{
    if (!check_arguments(in.size(), 2))
        return;
    int n;
    if (!convert_s(in[0], n))
        return;
    add_money(n);
    log << "Added " << in[0] << " to bank: " << in[1];
    for (vector<string>::iterator it = in.begin()+2; it != in.end(); ++it)
        log << " " << *it;
    log.add();
}

void Bank::cui_take_money(vector<string> in)
{
    if (!check_arguments(in.size(), 2))
        return;
    int n;
    if (!convert_s(in[0], n))
        return;
    if (!take_money(n))
    {
        syslog << "Cannot take intended amount of money: bank only has " << money;
        syslog.err();
        return;
    }
    log << "Took " << in[0] << " from bank: " << in[1];
    for (vector<string>::iterator it = in.begin()+2; it != in.end(); ++it)
        log << " " << *it;
    log.add();
}

void Bank::cui_set_interest_buy(vector<string> in)
{
    if (!check_arguments(in.size(), 1, 1))
        return;
    double d;
    if (!convert_s<double>(in[0], d))
        return;
    interest_buy = d;
    log << "Set interest on purchase to " << get_interest_buy() << "!";
    log.add();
}

void Bank::cui_set_interest_sell(vector<string> in)
{
    if (!check_arguments(in.size(), 1, 1))
        return;
    double d;
    if (!convert_s<double>(in[0], d))
        return;
    interest_sell = d;
    log << "Set interest on selling to " << get_interest_sell() << "!";
    log.add();
}

void Bank::cui_add_players(vector<string> in)
{
    if (!check_arguments(in.size(), 1))
        return;
    for (vector<string>::iterator it = in.begin(); it != in.end(); ++it)
    {
        add_player(*it);
        log << "New player: " << players.back();
        log.add();
    }
}

void Bank::cui_remove_players(vector<string> in)
{
    if (!check_arguments(in.size(), 1))
        return;
    for (vector<string>::iterator it = in.begin(); it != in.end(); ++it)
    {
        vector<Player>::iterator to_remove = check_player(*it);
        if (to_remove != players.end())
        {
            log << "Removed player: " << *to_remove;
            remove_player(to_remove);
            log.add();
        }
        else
        {
            syslog << "No player found with name or id '" << *it << "'";
            syslog.err();
        }
    }
}

void Bank::cui_add_chip_sorts(vector<string> in)
{
    if (!check_arguments(in.size(), 3))
        return;
    //check every group of three elements in 'in'
    for (int i = 0; (i+2) < in.size(); i++)
    {
        int amount, value;
        if (! (convert_s(in[i], amount) && convert_s(in[i+2], value)))
        {
            syslog << "Input '" << in[i] << " " << in[i+1] << " " << in[i+2] << "' is not correct to define a chip!";
            syslog.err();
            i += 2; //go to next group of three
            continue;
        }
        add_chip(Chip(value, in[i+1], amount));
        log << "Added new chip: " << chips[value];
        log.add();
    }
}

void Bank::cui_remove_chip_sorts(vector<string> in)
{
    if (!check_arguments(in.size(), 1))
        return;
    for (vector<string>::iterator it = in.begin(); it != in.end(); ++it)
    {
        int val;
        if (!convert_s(*it, val))
            continue;
        chips.erase(val);
    }
}

void Bank::cui_change_chip_amount(vector<string> in)
{
    vector< pair<int, int> > c = str_to_chips(in.begin(), in.end());
    for (vector< pair<int, int> >::iterator it = c.begin(); it != c.end(); ++it)
    {
        if (!check_chip_value(it->second))
            continue;
        change_chip_amount(it->second, it->first);
    }
}

void Bank::cui_deal_chips_all_players(std::vector<std::string> in)
{
    if (!check_arguments(in.size(), 1))
        return;
    deal_chips_all_players(str_to_chips(in.begin(), in.end()));
}

void Bank::cui_set_log(vector<string> in)
{
    if (!check_arguments(in.size(), 2, 3))
        return;
    Log* reflog = &log; //pointer to log (either 'log' or 'syslog') where user wants to change values
    // 1. parameter: choose log
    if (in.front() == "syslog")
        reflog = &syslog;
    else if (in.front() != "log")
    {
        syslog << "'" << in.front() << "' does not specify a log. Type 'log' for normal log or 'syslog' for system log.";
        syslog.err();
        return;
    }
    // 2. parameter: choose setting (without / with further paramter)
    if (in[1] == "save") //TODO same for load!
    {
        if (in.size() == 2)
        {
            if (reflog->save())
                syslog.add("Log successfully saved to standard path!");
            else
                syslog.add("Could not save log to standard path!");
        }
        else
        {
            if (reflog->save(in[2].c_str()))
            {
                syslog << "Log successfully saved to '" << in[2] << "'!";
                syslog.add();
            }
            else
            {
                syslog << "Could not save log to '" << in[2] << "'!";
                syslog.err();
            }
        }
        return;
    }
    else if (in[1] == "load")
    {
        if (in.size() == 2)
        {
            if (reflog->load())
                log.add("Log successfully loaded from standard path!");
            else
                log.add("Could not load log from standard path!");
        }
        else
        {
            if (reflog->load(in[2].c_str()))
            {
                log << "Log successfully loaded from '" << in[2] << "'!";
                log.add();
            }
            else
            {
                log << "Could not load log from '" << in[2] << "'!";
                syslog.err();
            }
        }
        return;
    }
    if (!check_arguments(in.size(), 3, 3))
        return;
    // 2. parameter: choose setting (with further paramter)
    if (in[1] == "file")
    {
        reflog->set_file_name(in[2]);
        syslog << "Changed filename of ";
        if (reflog == &log)
            syslog << "log";
        else
            syslog << "syslog";
        syslog << " to '" << in[2] << "'.";
        syslog.add();
    }
    else if (in[1] == "autosave")
    {
        int n;
        if (convert_s(in[2], n))
            reflog->set_autosave(n);
    }
    else
    {
        syslog << "'" << in[1] << "' is no available setting in logs!";
        syslog.err();
        return;
    }
}

void Bank::set_interest_buy(double interest)
{
    interest_buy = interest;
}

void Bank::set_interest_sell(double interest)
{
    interest_sell = interest;
}

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

void Bank::add_player(string& name)
{
    players.push_back(Player(name));
}

void Bank::remove_player(vector<Player>::iterator p)
{
    players.erase(p);
}

void Bank::add_chip(Chip chip)
{
    chips[chip.get_value()] = chip;
}

void Bank::remove_chip(int value)
{
    chips.erase(value);
}

bool Bank::change_chip_amount(int val, int diff)
{
    if (!check_chip_value(val))
        return false;
    if (diff > 0)
        chips[val].increase_amount(diff);
    else if (diff < 0)
        if (!chips[val].reduce_amount(-diff))
        {
            syslog << "No " << -diff << " chips of value " << val << " available!";
            syslog.err();
            return false;
        }
    return true;
}

void Bank::deal_chips_all_players(vector< pair<int, int> > chips)
{
    log << "Change amount of chips at each player as following:\nAdd: ";
    stringstream take;
    int diff = 0;
    for (vector< pair<int, int> >::iterator c = chips.begin(); c != chips.end(); ++c)
    {
        if (!change_chip_amount(c->second, -(c->first * players.size())))
            continue;
        if (c->first > 0)
            log << " " << c->first << "x" << c->second;
        else if (c->first < 0)
            take << " " << -(c->first) << "x" << c->second;
        else
            continue;
        diff -= c->first * c->second;
    }
    int diffbank = diff * int(players.size());
    chips_players -= diffbank; //update 'chips_players'
    log << "\nTake:" << take.str() << "\nResult player: " << -diff << "  ***  Result bank: " << diffbank;
    log.add();
}

vector<Player>::iterator Bank::check_player(string name)
{
    return find_if(players.begin(), players.end(), [&name](Player p) -> bool {try {if ((p.get_name() == name) || (p.get_id() == boost::lexical_cast<int>(name))) return true; else return false;} catch(boost::bad_lexical_cast&){return false;};});
}

int Bank::get_balance()
{
    int ret = 0;
    for (map<int, Chip>::iterator it = chips.begin(); it != chips.end(); ++it)
    {
        ret += it->second.get_amount() * it->second.get_value();
    }
    return ret;
}

string Bank::get_interest_buy()
{
    stringstream sstr;
    sstr << interest_buy*100 << "%";
    return sstr.str();
}

string Bank::get_interest_sell()
{
    stringstream sstr;
    sstr << interest_sell*100 << "%";
    return sstr.str();
}

void Bank::show_money()
{
    log << "Money in bank: " << money;
    log.add();
}

void Bank::show_chips_players()
{
    log << "Value of all chips belonging to players: " << chips_players;
    log.add();
}

void Bank::show_interest()
{
    log << "Interest: " << get_interest_buy() << " (buy) / " << get_interest_sell() << " (sell)";
    log.add();
}

void Bank::show_chip_value()
{
    log << "Value of all chips in bank: " << get_balance();
    log.add();
}

void Bank::show_chips()
{
    log << "Chips in bank:";
    for (map<int, Chip>::iterator it = chips.begin(); it != chips.end(); ++it)
    {
        log << "\n" << it->second;
    }
    log.add();
}

void Bank::show_bank_status()
{
    show_money();
    show_chip_value();
    show_chips();
}

void Bank::show_players()
{
    log << "All players registred to bank:";
    for (vector<Player>::iterator p = players.begin(); p != players.end(); ++p)
    {
        log << "\n" << p->tostr();
    }
    log.add();
}

void Bank::exit_program()
{
    syslog.add("End running of PokerBank and leave program now...");
    throw exit_exception(0);
}

vector< pair<int, int> > Bank::str_to_chips(vector<string>::iterator first, vector<string>::iterator last)
{
    vector< pair<int, int> > ret;
    //split words fo input in the two numbers: "4x50" --> n[0]=4 n[1] =50
    for (vector<string>::iterator it = first; it != last; ++it)
    {
        vector<string> n;
        boost::split(n, *it, [](const char c)->bool{return c == 'x';});
        if (n.size() != 2)
        {
            syslog << "'" << *it << "': Incorrect way to specify chip sort";
            syslog.err();
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
            syslog << "'" << *it << "': Chip amount and sort must be specified by numbers!";
            syslog.err();
            continue;
        }
        ret.push_back(pair<int, int>(amount, value));
    }
    return ret;
}

void Bank::buy_sell(bool buy, string name, vector< pair<int, int> > buychips)
{
    int brutto;
    vector<Player>::iterator p = check_player(name);
    if (p != players.end())
        log << *p;
    else
        log << "\"" << name << "\"(unknown)";
    if (buy)
        log << " bought";
    else
        log << " sold";

    for(vector< pair<int, int> >::iterator it = buychips.begin(); it != buychips.end(); ++it)
    {
        if (it->first == 0) //transfer no chips of this sort
            continue;
        //check if sort exists
        if (!check_chip_value(it->second))
            continue;
        if (buy)
        {
            //check if intended amount of chips available
            if (!chips[it->second].reduce_amount(it->first))
            {
                syslog << "Could not buy " << it->first << " chips of sort '" << it->second << "': only " << chips[it->second] << " chips available!";
                syslog.err();
                continue;
            }
        }
        else
            chips[it->second].increase_amount(it->first);

        brutto = it->first * it->second;
        log << " " << it->first << "x" << it->second << " (" << brutto << ");";

        //update 'chips_players'
        if (buy)
            chips_players += brutto;
        else
            chips_players -= brutto;
    }
    //put log entry
    if (brutto != 0)
    {
        int interest, netto;
        //(always round interest up)
        if (buy)
        {
            interest = ceil(brutto * interest_buy);
            netto = brutto + interest;
            money += netto;
            log << "\nResult: " << brutto << "  ***  Interest(" << get_interest_buy() << "): " << interest << "  ***  Please pay: ";
        }
        else
        {
            interest = ceil(brutto * interest_sell);
            netto = brutto - interest;
            money -= netto;
            log << "\nResult: " << brutto << "  ***  Interest(" << get_interest_sell() << "): " << interest << "  ***  You get: ";
        }
        log << netto;
        log.add();
    }
    else
    {
        log.ref_buff().str("");
        syslog.err("No correct inputs - no chips transferred!");
    }
}

bool Bank::check_arguments(size_t is, size_t min, size_t max)
{
    stringstream sstr;
    sstr << "Expected ";
    if (max == -1)
        if (is >= min)
            return true;
        else
            sstr << "at least " << min;
    else if (is >= min && is <= max)
        return true;
    else
    {
        if (min == max)
            sstr << min;
        else
            sstr << "between " << min << " and " << max;
    }
    sstr << " arguments!";
    syslog.err(sstr.str());
    return false;
}

bool Bank::check_chip_value(int& val)
{
    if (chips.find(val) == chips.end())
    {
        syslog << "Sort '" << val << "' does not exist!";
        syslog.err();
        return false;
    }
    return true;
}

template<class T> bool Bank::convert_s(string& source, T& var)
{
    try
    {
        var = boost::lexical_cast<T>(source);
    }
    catch (boost::bad_lexical_cast&)
    {
        syslog << "'" << source << "' has wrong type!";
        syslog.err();
        return false;
    }
    return true;
}
