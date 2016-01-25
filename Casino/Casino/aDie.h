//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef ADIE_H
#define ADIE_H

#include "RandomNumber.h" //includes definition of aRandomNumber class
//	Simulate a 6 sided die
//	Allows user to use a 6 sided die

class aDie: public RandomNumber
{
public:
	aDie(); //default constructor creates the 6 sided die
	~aDie();
	int roll(); //rolls a die
	operator int(); //converts aDie to an int
};


#endif