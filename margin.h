/*  
    This program was developed by Hsiao Weng
    Copyright 2016, Common Development and Distribution License
    This code is open source
*/

/* 
    File:   margin.h
    Author: Hsiao W.    
 */

#ifndef MARGIN_H
#define MARGIN_H

#include<limits>

//declare class margin
class Margin { 
//declare private members
private:
    double minmax; 
    
//declare public members
public:
    Margin();
    ~ Margin();
    void calc_margin();
};

#endif /* MARGIN_H */

