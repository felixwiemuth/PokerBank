/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef CUI_H_INCLUDED
#define CUI_H_INCLUDED

#include "Command.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <map>


template <class FuncClass>
class Cui
{
    typedef typename std::map< std::string, Command<FuncClass> >::iterator cmds_iter;

    public:
        Cui()
        {
            help_cmd = "help";
            help_all_cmd = "commands";
            exit_cmd = "exit";
            reset_help();
            msg_exit = "Leaving CUI environment...";
            err = "Error: ";
            err_no_command_1 = "'";
            err_no_command_2 = "' is not a command!";
            err_wrong_call_1 = "No function defined to call '";
            err_wrong_call_2 = "' without parameters!";
            err_wrong_call_p_1 = "No function defined to call '";
            err_wrong_call_p_2 = "' with parameters!";
            err_no_object_defined_1 = "No object specified to execute '";
            err_no_object_defined_2 = "' on!";
        }


    private:
        std::map< std::string, Command<FuncClass> > cmds; //all possible commands
        std::string help_cmd; //command to show help (general or for command)
        std::string help_all_cmd; //string to type behind 'help_cmd' to execute 'show_all_help()'
        std::string exit_cmd; //command to leave 'run()' (can be overwritten by commands in 'cmds')
        //messages
        std::string help; //help text
        std::string msg_exit; //message on exit
        //error messages
        std::string err;
        std::string err_no_command_1;
        std::string err_no_command_2;
        std::string err_wrong_call_1;
        std::string err_wrong_call_2;
        std::string err_wrong_call_p_1;
        std::string err_wrong_call_p_2;
        std::string err_no_object_defined_1;
        std::string err_no_object_defined_2;


    public:
        void run()
        {
            //TODO check if messages valid / set to std
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
                cmds_iter cmd = cmds.find(words.front());
                if (cmd != cmds.end())
                {
                    //words[0] == command -- words[1]...words[n] == values
                    int execode; //exitcode

                    //call method without/with paramter
                    if (words.size() == 1)
                        execode = cmd->second.execute();
                    else
                        execode = cmd->second.execute(std::vector<std::string>(words.begin()+1, words.end()));

                    //print error message belonging to exitcode
                    switch(execode)
                    {
                        case 0:
                            //everything o.k.
                            break;
                        case 1:
                            //message sent by Command if enabled
                            break;
                        case 2:
                            std::cout << err << err_no_object_defined_1 << words.front() << err_no_object_defined_2 << std::endl;
                            break;
                        case 3:
                            std::cout << err << err_wrong_call_1 << words.front() << err_wrong_call_2 << std::endl;
                            break;
                        case 4:
                            std::cout << err << err_wrong_call_p_1 << words.front() << err_wrong_call_p_2 << std::endl;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    if (words.front() == help_cmd)
                    {
                        if (words.size() == 1)
                            std::cout << help << std::endl;
                        else //words.size() > 1
                        {
                            cmd = cmds.find(words[1]);
                            if (cmd != cmds.end())
                                cmd->second.show_help();
                            else
                            {
                                if (words[1] == help_all_cmd)
                                    show_all_help();
                                else
                                    std::cout << err << err_no_command_1 << words[1] << err_no_command_2 << std::endl;
                            }
                        }
                    }
                    else if (words.front() == exit_cmd)
                    {
                        if (words.size() == 1)
                        {
                            std::cout << msg_exit << std::endl;
                            return;
                        }
                        else
                            std::cout << err << err_wrong_call_p_1 << words.front() << err_wrong_call_p_2 << std::endl;
                    }
                    else
                        std::cout << err << err_no_command_1 << words.front() << err_no_command_2 << std::endl;
                }
            }
        }

        void reset_help()
        {
            help = "Type 'help <command>' for information about commands!\n"
                   "Type 'help " + help_all_cmd + "' for information about all commands!";
        }

        void show_all_help()
        {
            for (cmds_iter it = cmds.begin(); it != cmds.end(); ++it)
            {
                std::cout << "'" << it->first << "': ";
                it->second.show_help();
            }
        }

        Command<FuncClass>& operator[] (const std::string& s) //returns reference to command 's' in 'cmds' if available, otherwise adds command 's'
        {
            return cmds[s];
        }
};


#endif // CUI_H_INCLUDED
