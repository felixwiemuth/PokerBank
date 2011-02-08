/*
 * File:   main.cpp
 * Author: Felix Wiemuth
 *
 * Created on 7. Februar 2011, 15:00
 */

//#include <stdlib.h>
#include <iostream>

#include "Bank.h"

using namespace std;

/*
 *
 */
int main(/*int argc, char** argv*/) {
    Bank bank;
    Bank bank2;
    cout << "Banks balance: " << bank2.get_balance() << endl;
    Chip c1(100, "MaanxD", 5);
    cout << "Chip 1: " << c1;
    return 0;
}

