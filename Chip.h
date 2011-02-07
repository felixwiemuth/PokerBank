/* 
 * File:   Chip.h
 * Author: Felix
 *
 * Created on 7. Februar 2011, 15:11
 */

#ifndef _CHIP_H
#define	_CHIP_H

#include <string>

using namespace std;

class Chip {
public:
    Chip();
    Chip(int value, std::string name, int amount);
private:
    int value; //value of this chip type
    std::string name; //description of this chip type
    int amount; //number of chips in bank
public:
    void print();
    ostream& operator<<(); //todo: make possible "cout << Chip" or "sstr << Chip"



};

#endif	/* _CHIP_H */

