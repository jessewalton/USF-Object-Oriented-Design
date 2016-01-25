//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include <iostream>
#include "RandomNumber.h" //includes definition of aRandomNumber class
#include "aDie.h" //includes definition of aDie class
using namespace std;

aDie::aDie() //default constructor of a 6 sided die.
{
	setRange(1,6);
}

aDie::~aDie()
{

}

int aDie::roll() //rolls the die generating a result between 1 and 6 
{
	return generate();
}

aDie::operator int()
{
	return generate();
}