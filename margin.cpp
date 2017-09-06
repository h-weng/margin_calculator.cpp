/*  
    This program was developed by Hsiao Weng
    Copyright 2016, Common Development and Distribution License
    This code is open source
*/

/* 
    File:   margin.cpp
    Author: Hsiao W.    
 */


#include <stdio.h>      /* printf */
#include <stdlib.h>     /* abs */
#include <math.h>       /* remainder */
#include <cmath> /* abs */

#include "trading.h"
#include "margin.h"

//constructor for margin class for creating the object
Margin::Margin() {
 
}

//destructor for margin class for destroying the object
Margin::~Margin() {
    
}

void Margin::calc_margin() {
    try { //pass a double through cin and assign it to variable
        cout << "\nEnter Stop loss reference: ";
        cin >> minmax; 
        //if the assignment fails, display error and callback function
        while(cin.fail()) { 
            cin.clear();
            cin.ignore(numeric_limits <streamsize>::max(), '\n');
            cout << "\n... Invalid.  Enter valid values ..." << endl;
            calc_margin();
        }  
    } catch (exception& e) { //catch errors and callback to calc_margin()
        cout << "\n... Invalid.  Enter valid values ..." << endl;
        calc_margin();
    }
    
    //create an object from the trading class with address of input parameter
    Trading objs(&minmax);
    //call to trading class methods on the object
    objs.make();
    objs.set_pairs();
    objs.calculate();
}

//constructor for trading class for creating the object
Trading::Trading() {
    
}

//destructor for trading class for destroying the object
Trading::~Trading() {
    
}

//overloaded constructor for trading class passing pointer to minmax
Trading::Trading(double* minmax) {
    key_level = *minmax; 
}

//method for clearing the screen
void Trading::clear_screen() {
    cout << "\033[2J"; //clears the entire screen
    cout << "\033[h"; //moves to the top of the screen
}

//method definition for getting the balance and setting the leverage
void Trading::make() {
    get_balance();
    set_leverage();
}

//method definition for setting the pair of curencies and their attributes
void Trading::set_pairs() {
    pairs();
    pair_base();
    pair_quote();
    pair_check();
    
}

//method for getting the balance
void Trading::get_balance() {
    try {
         //pass an int through cin and assign it to a variable 
        cout << "\nEnter your current balance(no cents): ";
        cin >> balance;
        //if the assignment fails, display error and callback function
        while(cin.fail()) { 
            cin.clear();
            cin.ignore(numeric_limits <streamsize>::max(), '\n');
            cout << "\n... Invalid.  Enter valid values ..." << endl;
            get_balance();
        }
    } catch (exception& e) { //catch errors and callback to get_balance()
        cout << "\n... Invalid.  Enter valid values ..." << endl;
        get_balance();
    }
}

//method for setting leverage
void Trading::set_leverage() { 
    //try to pass through cin to leverage 
    try { 
        cout << "Enter the leverage ratio: ";
        cin >> leverage;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits <streamsize>::max(), '\n');
            cout << "\n... Invalid.  Enter valid values ..." << endl;
            get_balance();
        }
    //catch errors and callback to set_leverage()
    } catch (exception& e) { 
        cout << "\n... Invalid.  Enter valid values ..."  << endl;
        set_leverage();
    }
}

//method definition for writing currency pair to file
void Trading::pair_write() {
    //create an ofstream object named fout and write to file
    try {
        ofstream fout("data.txt"); 
        
        transform(base.begin(), base.end(), base.begin(), ::toupper);
        fout << base << endl;
   
        transform(quote.begin(), quote.end(), quote.begin(), ::toupper);
        fout << quote << endl;
        
        fout.close();
    } catch (exception& e) {
        cout << "\n... Invalid file ...";
    }
}

//method for displaying usable pairs
void Trading::pairs() {
    cout << "\n230/50:\t   EUR/CAD   EUR/GBP   EUR/NZD   EUR/USD   USD/CAD";
    cout << "\n260/33:\t   AUD/CAD   AUD/USD";
    cout << "\n330/33:\t   EUR/AUD" << endl;
}

//method definition for checking if the pair has been previously used
void Trading::pair_check() {
    string pair_ch[2];
    string base_prev, quote_prev;
    ifstream file("data.txt");
    if (file.is_open()) {
        for(int i = 0; i < 2; i++) {
            getline(file, pair_ch[i]);
        }
    }
    file.close();
    base_prev = pair_ch[0];
    quote_prev = pair_ch[1];
    
    if (base != base_prev && quote != quote_prev) {
        try {
            ofstream fout("data.txt"); //create an ofstream object named

            transform(base.begin(), base.end(), base.begin(), ::toupper);
            fout << base << endl;

            transform(quote.begin(), quote.end(), quote.begin(), ::toupper);
            fout << quote << endl;
        
            fout.close();
        } catch (exception& e) {
            cout << "\n... Invalid file ...";
        }  
    } else if (base == base_prev && quote == quote_prev) {
        cout << "... Used in previous trade.  Use another pair ...";
        pair_check();
    } else {
        
    }
}

//method definition for delcaring the base pair
void Trading::pair_base() {
    bool t = false;
    //ask for user input of currency base
    try {
        cout << "\n   Enter the base currency of pair.\n   (BASE/quote): ";
        cin >> base;
        transform(base.begin(), base.end(), base.begin(), ::toupper);
        //check if the pair is in the array of usable currencies
        for (int i = 0; i < 9; i++) {
            if (base.compare(currencies[i]) == 0) {
                t = true;
            } 
        }
        //generate error if entry is not found and callback method
        if (t == false) {
            cout << "\n... Invalid.  Enter valid values ..."  << endl;
            pair_base();
        }
    //generate error if exception error, method callback 
    } catch (exception& e) {  
        cout << "\n... Invalid.  Enter valid value ..." << endl;
        pair_base();
    }
}

//method definition for declaring the quote pair
void Trading::pair_quote() {
    bool t = false;
    //ask for user input of currency quote
    try {
        cout << "\n   Enter the quote currency of pair.\n   (base/QUOTE): ";
        cin >> quote;
        transform(quote.begin(), quote.end(), quote.begin(), ::toupper);
        for (int i = 0; i < 10; i++) {
            if (quote.compare(currencies[i]) == 0) {
                t = true;
            } 
        }
        //generate error if entry is not found and callback method
        if (t == false) {
            cout << "\n... Invalid.  Enter valid values ..."  << endl;
            pair_quote();
        } 
    //generate error if exception error, method callback 
    } catch (exception& e) {
        cout << "\n... Invalid.  Enter valid value ..." << endl;
        pair_quote();
    }
}

//method definition for calculating the margin
void Trading::calculate() {
    double size_lots, margin_spc;
    double spc_round = 30.0;
    
    //calculate pip value and space for magin call
    try {
        //use this to calculate size and pip value if quote is equal to USD
        if (mybase == quote) {
            //call to methods to get values
            mybase_is_quote();
            margin_spaced();
            
            //set margin_spc to value from margin_space() times mypip_value
            margin_spc = margin_space * mypip_value;
            margin_spc = margin_spc - fmod(margin_spc, spc_round);
            
            size_lots = ((balance - margin_spc) / margin_base) * leverage;
            //cast size to int 
            size = (int) size_lots;
            //estimate size by subtracting modulus of a round number
            size_estimate = size - (size % lot_round);
            pip_value = quote_ref * size_estimate;
            print_calculation();
        } else if (currencies[3] == base && currencies[2] == quote) {
            //call to methods to get values
            myquote_is_cad();
            margin_spaced();
            
            //set margin_spc to value from margin_space() times mypip_value
            margin_spc = margin_space * mypip_value;
            margin_spc = margin_spc - fmod(margin_spc, spc_round); //(margin_spc % spc_round);
            
            size_lots = ((balance - margin_spc) / eur_usd_base ) * leverage;
            //cast size to int 
            size = (int) size_lots;
            //estimate size by subtracting modulus of a round number
            size_estimate = size - (size % lot_round);
            //set pip_value
            pip_value = quote_ref * size_estimate * margin_base;
            
             //call to print_calculation method  
            print_calculation(); 
        }  else {//in all other cases use this to calculate size and pip value
            //call to methods to get values
            mybase_is_base();
            margin_spaced();
            
            //set margin_spc to value from margin_space() times mypip_value
            margin_spc = margin_space * mypip_value;
            
            margin_spc = margin_spc - fmod(margin_spc, spc_round);
            
            size_lots = ((balance - margin_spc) / (eur_usd_base))  * leverage;
            //cast size to int 
            size = (int) size_lots;
            //estimate size by subtracting modulus of a round number
            size_estimate = size - (size % lot_round);
            //set pip_value
            pip_value = quote_ref * size_estimate * (1/margin_base);
            
            //call to print_calculation method
            print_calculation();         
        }   
    } catch (exception& e) { //generate error if entry is not found, method callback  
        cout << "\n... Invalid.  Enter valid value ..." << endl;
        calculate();
    }
}

//method for finding the margin space
void Trading::margin_spaced() { 
    double margin_pips_convert, raw_pips;
    try {
        raw_pips = abs(price - key_level);
        margin_pips_convert = (margin_round * raw_pips);
        margin_space = (int) margin_pips_convert + pips_tolerance;
        cout << "\n... Stop distance (pips): " << margin_space <<  " (unadjusted: " << (int) margin_pips_convert << ") ...";
    //generate error if entry is not found, method callback 
    } catch (exception& e) {  
        cout << "\n... Invalid.  Enter valid value ..." << endl;
        margin_spaced();
    }
}

//method for calculating the lot size if base is usd
void Trading::mybase_is_base() { 
    double size_lots, eur_usd_price;
    try {
        cout << "\n   Enter current price of " << base << "/" << quote << ": ";
        cin >> price;
        
        cout << endl;
        cout << "   Enter current price for EUR/USD: ";
        cin >> eur_usd_price;
        
        //set margin_Base to base price
        margin_base = price;
        eur_usd_base = eur_usd_price;
        
        //size of lot is balance divided by EUR/USD times leverage
        size_lots = (balance/eur_usd_base) * leverage;
        //cast size to int
        size = (int) size_lots;
        //value of a pip
        mypip_value = quote_ref * size * (1/margin_base);
    } catch (exception& e) {
        cout << "\n... Invalid.  Enter valid values ..." << endl;
        mybase_is_base();
    }
}

//method for calculating the lot size if quote is usd
void Trading::mybase_is_quote() { 
    double size_lots, quote_price;
    try {
        cout << "\n   Enter current price of " << base << "/" << quote << ": ";
        cin >> price;
        
        //set margin_base to base price
        margin_base = price;
        
        //size of lot is balance divided by margin_base times leverage
        size_lots = (balance/margin_base) * leverage;
        //cast size to int
        size = (int) size_lots;
        //value of a pip
        mypip_value = quote_ref * size;
    } catch(exception& e) { //generate error if input is invalid
        cout << "\n... Invalid.  Enter valid values ..." << endl;
        mybase_is_quote();
    }
}

//method for calculating the lot size if quote is cad
void Trading::myquote_is_cad() { 
    double size_lots, quote_price = 0.0, eur_usd_price = 0.0;
    
    try { //try and ask for the current price of */CAD and price of EUR/USD
        cout << "\n   Enter current price of " << base << "/" << quote << ": ";
        cin >> price;
       
        cout << endl;
        cout << "   Enter current price for " << mybase + "/" << quote << ": ";
        cin >> quote_price;
        
        cout << endl;
        cout << "   Enter current price for EUR/USD: ";
        cin >> eur_usd_price;
        
        //set margin_base to 1(*/CAD)
        margin_base = 1/quote_price;
        eur_usd_base = eur_usd_price;
        
        //size of lot is balance divided by EUR/USD times leverage
        size_lots = (balance/eur_usd_base) * leverage;
        //cast size to int
        size = (int) size_lots;
        //value of a pip
        mypip_value = quote_ref * margin_base * size;
    } 
    catch (exception& e)
    {  
        cout << "\n... Invalid.  Enter valid values ..." << endl;
        myquote_is_cad();
    }
}

//method for printing calculations on screen
void Trading::print_calculation() { 
    if (size > 0) {
        cout << "\n... optimium number of units: " << size_estimate <<
                " (unadjusted: " << size << ") ..." << endl;
        cout << "\n... point in percentage value: ";
        cout.precision(4);
        cout << fixed << pip_value << " ..." << endl;
    } 
    else 
    {
        cout << "\n... Not enough to cover margin space ..." << endl;
    }
}