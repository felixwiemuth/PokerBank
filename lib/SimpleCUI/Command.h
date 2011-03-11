/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>


template <class FuncClass>
class Command
{
    typedef void (FuncClass::*Mptr)();
    typedef void (FuncClass::*Mptr_val)(std::vector<std::string>);

    public:
        Command()
        {
            available = true;
            err_msg = 0;
            obj = 0;
            mptr = 0;
            mptr_val = 0;
        }

        Command(FuncClass* obj, Mptr mptr, Mptr_val mptr_val=0) : obj(obj), mptr(mptr), mptr_val(mptr_val)
        {
            available = true;
            err_msg = 0;
        }


    private:
        bool available; //methods in 'mptr' and 'mptr_val' can only be executed if set 'true' -- otherwise '*err_msg' is shown
        std::vector<std::string> err_msg_store; //container of messages that include reasons why this method is not available
        std::string* err_msg; //activated message of 'err_msg_store'
        std::string help; //description of this command
        FuncClass* obj; //object to execute function on
        void (FuncClass::*mptr)(); //pointer to function with no parameters
        void (FuncClass::*mptr_val)(std::vector<std::string>); //pointer to function with parameter


    public:
        Command<FuncClass>& set(const Command<FuncClass>& other) //replace '*this' with 'other'
        {
            *this = other;
            return *this;
        }

        Command<FuncClass>& set(FuncClass* obj, Mptr mptr, Mptr_val mptr_val=0) //'set(...)' as "constructor" version
        {
            return set(Command<FuncClass>(obj, mptr, mptr_val));
        }

        void set_help(std::string s)
        {
            help = s;
        }

        void add_err_msg(std::string s) //adds an error messages to the error message container
        {
            err_msg_store.push_back(s);
        }

        void set_err_msg(unsigned int n) //sets the active error message to string with index 'n' in 'err_msg_store'
        {
            if (n < err_msg_store.size())
                err_msg = &err_msg_store[n];
        }

        void point_err_msg(std::string* s_ptr) //sets the active error message to the string 's_ptr' points to
        {
            err_msg = s_ptr;
        }

        void activate()
        {
            available = true;
        }

        void deactivate(unsigned int n = -1)
        {
            available = false;
            if (n != -1)
                set_err_msg(n);
        }

        int check_valid() //return value: 0 = execution of 'mptr' or 'mptr_val' would be valid (regarding 'available' and 'obj') 1 = not available 2 = obj==0
        {
            if (!available)
            {
                if (err_msg != 0)
                    std::cout << *err_msg << std::endl;
                return 1;
            }
            if (obj == 0)
            {
                return 2;
            }
            return 0;
        }

        int execute() //return values: 0-2: 'check_valid()' 3 = no 'mptr' defined
        {
            int ret = check_valid();
            if (ret != 0)
                return ret;
            if (mptr == 0)
            {
                return 3;
            }
            ((*obj).*mptr)();
            return 0;
        }

        int execute(std::vector<std::string> values) //return values: 0-2: 'check_valid()' 4 = no 'mptr_val' defined
        {
            int ret = check_valid();
            if (ret != 0)
                return ret;
            if (mptr_val == 0)
            {
                return 4;
            }
            ((*obj).*mptr_val)(values);
            return 0;
        }

        void show_help()
        {
            if (help.length() != 0)
                std::cout << help << std::endl;
            else
            {
                std::cout << "No help for this command." << std::endl;
            }
        }
};


#endif // COMMAND_H_INCLUDED
