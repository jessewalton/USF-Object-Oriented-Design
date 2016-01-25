//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

//	Generates a random number
//	Allows user to set the range of the random number

class RandomNumber
{
private:
	int rangeMin;
	int rangeMax;


public:
	RandomNumber(); //Default Constructor
	RandomNumber(int min, int max);	//Constructor, sets range
	~RandomNumber();
	void setRange(int a, int b);	//Sets range, a sets the minimum number, b sets the maximum number
	int getRangeMin();	//Returns the minimum value of the number's range
	int getRangeMax();	//Returns the maximum value of the number's range
	int generate();	//Generates and returns a random number
	operator int(); //converts RandomNumber to an int
};


#endif