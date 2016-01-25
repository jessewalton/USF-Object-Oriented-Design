//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include <cstdlib>			// Class uses rand()
#include "RandomNumber.h"	// Includes definition of RandomNumber class

using namespace std;

int rangeMin;
int rangeMax;

RandomNumber::RandomNumber()	// Default Constructor
{
	setRange(0, 0);
}

RandomNumber::RandomNumber(int min, int max)	//Constructor, sets the min and max of the range
{
	if (min>max)
	{
		int Temp = max;
		max = min;
		min = Temp;
	}
	setRange(min, max);
}

RandomNumber::~RandomNumber()
{

}

void RandomNumber::setRange(int a, int b)	//Uses a to set the lowest possible number, uses b to set the highest number possible
{
	rangeMin = a;
	rangeMax = b;
}

int RandomNumber::getRangeMin()	//returns variable rangeMin
{
	return rangeMin;
}

int RandomNumber::getRangeMax()	//returns variable rangeMax
{
	return rangeMax;
}


int RandomNumber::generate()	//Generates and returns a random number within a specified range
{
	return (rand() % rangeMax) + rangeMin;
}

RandomNumber::operator int() //returns generate as an int
{
	return generate();
}
