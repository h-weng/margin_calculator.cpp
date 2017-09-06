/*  
    This program was developed by Hsiao Weng
    Copyright 2016, Common Development and Distribution License
    This code is open source
*/

/* 
    File:   margin.h
    Author: Hsiao W.    
 */

#ifndef TRADING_H
#define TRADING_H

#include<iostream>
#include <fstream>
#include<cctype>
#include <algorithm>
#include <string>
using namespace std;

//declare class margin
class Trading { 
//declare private members
private:
    string mybase = "USD";
    string base;
    string quote;
    double price, pip_value, key_level;
    int balance, leverage, margin_space, size, size_estimate;
    double margin_base, eur_usd, eur_usd_base, mypip_value;
    int lot_round = 1000, margin_round = 10000, pips_tolerance = 23;
    double quote_ref = 0.0001;
    const char* currencies[9] = { "USD", "AUD", "CAD", "EUR", "CHF", "GBP", "NZD", 
                            "XAU", "XAG" }; 
//declare public members
public:
    Trading(double* MinMax);
    Trading();
    ~ Trading();
    void clear_screen();
    void make();
    void set_pairs();
    void get_balance();
    void set_leverage();
    void pair_write();
    void pairs();
    void pair_check();
    void pair_base();
    void pair_quote();
    void calculate();
    void margin_spaced();
    void mybase_is_base();
    void mybase_is_quote();
    void myquote_is_cad();
    void print_calculation();
};

#endif /* TRADING_H */

