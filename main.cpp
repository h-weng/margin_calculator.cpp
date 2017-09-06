/*  
    This program was developed by Hsiao Weng
    Copyright 2016, Common Development and Distribution License
    This code is open source
*/

/* 
    File:   main.cpp
    Author: Hsiao W.    
 */

#include <cstdlib>
#include <iostream>
#include "margin.h"

using namespace std;

//method for clearing the screen
void clear_screen() {
    cout << "\033[2J" << endl; //clears the entire screen
    cout << "\033[h" << endl; //moves to the top of the screen 
}

//main method; program begins here
int main() {
    clear_screen();
    cout << "\n.. Margin Calculator 1.0 ..." << endl;
    Margin obj;
    obj.calc_margin();
    return 0;
}

