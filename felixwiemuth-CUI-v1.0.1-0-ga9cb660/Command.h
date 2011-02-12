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
    public:
        Command(FuncClass* obj, std::string name, void (FuncClass::*mptr)(), void (FuncClass::*mptr_val)(std::vector<std::string>)=0) : name(name), obj(obj), mptr(mptr), mptr_val(mptr_val)
        {

        }
    private:
        std::string name; //command name by which it is called
        FuncClass* obj; //object to execute function on
        void (FuncClass::*mptr)(); //pointer to function with no parameters
        void (FuncClass::*mptr_val)(std::vector<std::string>); //pointer to function with parameter

    public:
        std::string get_name()
        {
            return name;
        }
        bool execute ()
        {
            if (mptr != 0)
            {
                ((*obj).*mptr)();
                return true;
            }
            return false;
        }
        bool execute(std::vector<std::string> values)
        {
            if (mptr_val != 0)
            {
                ((*obj).*mptr_val)(values);
                return true;
            }
            return false;
        }
};


#endif // COMMAND_H_INCLUDED
