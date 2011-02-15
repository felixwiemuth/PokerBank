/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef CUI_H_INCLUDED
#define CUI_H_INCLUDED

#include "Command.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>


template <class FuncClass>
class Cui
{
    public:
        Cui()
        {
            exit_cmd = "exit";
            msg_exit = "Leaving CUI environment...";
            err = "Error: ";
            err_no_command_1 = "'";
            err_no_command_2 = "' is not a command!";
            err_wrong_call_1 = "Error: No function defined to call '";
            err_wrong_call_2 = "' without parameters!";
            err_wrong_call_p_1 = "Error: No function defined to call '";
            err_wrong_call_p_2 = "' with parameters!";
        }
    private:
        std::vector< Command<FuncClass> > cmds; //all possible commands
        std::string exit_cmd; //command to leave 'run()' (can be overwritten by commands in 'cmds')
        //messages
        std::string msg_exit;
        //error messages
        std::string err;
        std::string err_no_command_1;
        std::string err_no_command_2;
        std::string err_wrong_call_1;
        std::string err_wrong_call_2;
        std::string err_wrong_call_p_1;
        std::string err_wrong_call_p_2;
    public:
        void add_command(FuncClass* obj, std::string name, void (FuncClass::*mptr)(), void (FuncClass::*mptr_val)(std::vector<std::string>)=0)
        {
            cmds.push_back(Command<FuncClass>(obj, name, mptr, mptr_val));
        }
        void add_command(Command<FuncClass>& cmd)
        {
            cmds.push_back(cmd);
        }
        void run()
        {
            std::string in;
            while(true)
            {
                std::cout << std::endl;
                std::cout << "> ";
                getline(std::cin, in);
                std::cout << std::endl;
                std::vector<std::string> words;
                boost::split(words, in, [](const char c)->bool{return c == ' ';});
                //check if command
                int cmd = -1;
                for (int i = 0; i < cmds.size(); i++)
                {
                    if (cmds[i].get_name() == words.front())
                    {
                        cmd = i;
                        break;
                    }
                }
                if (cmd == -1) //not a command
                {
                    //if no 'exit_cmd' command is defined, typing 'exit_cmd' leads to leave the 'run()' method of 'Cui'
                    if (in == exit_cmd)
                    {
                        std::cout << msg_exit << std::endl;
                        return;
                    }
                    std::cout << err << err_no_command_1 << words.front() << err_no_command_2 << std::endl;
                    continue;
                }
                //words[1]...words[n] == values
                if (words.size() == 1)
                {
                    if (!cmds[cmd].execute())
                        std::cout << err_wrong_call_1 << words.front() << err_wrong_call_2 << std::endl;
                }
                else
                {
                    if (!cmds[cmd].execute(std::vector<std::string>(words.begin()+1, words.end())))
                        std::cout << err_wrong_call_p_1 << words.front() << err_wrong_call_p_2 << std::endl;
                }
            }
        }
};


#endif // CUI_H_INCLUDED
