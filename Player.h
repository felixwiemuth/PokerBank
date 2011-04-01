/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>

class Player
{
    static int nextid;
    public:
        Player();
        Player(std::string name);
    private:
        std::string name;
        int id;
    public:
        std::string get_name();
        std::string tostr() const;
        friend std::ostream& operator<<(std::ostream& os, const Player& p);

    private:
        void init();
};



#endif // PLAYER_H_INCLUDED
