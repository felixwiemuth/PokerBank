/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef _CHIP_H
#define	_CHIP_H

#include <string>



class Chip
{
    public:
        Chip();
        Chip(int value, std::string name, int amount);
    private:
        int value; //value of this chip type
        std::string name; //description of this chip type
        int amount; //number of chips in bank
    public:
        void increase_amount (int n); //increases 'amount' by n
        bool reduce_amount(int n); //reduces 'amount' by 'n' -- returns 'true' when enough chips available ('amount>=n')
        void factor_value(double& factor);
        friend std::ostream& operator<<(std::ostream& os, const Chip& chip);
        friend bool operator<(const Chip& c1, const Chip& c2);
        const int& operator[](int i);

        //get_ methods
        int get_value();
        int get_amount();
};



#endif	/* _CHIP_H */

