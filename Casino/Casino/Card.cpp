#include "Card.h"
#include <stdexcept>
#include <iostream>
using namespace std;

const string Card::suits[4] = {"Diamonds", "Hearts", "Clubs", "Spades"};
const string Card::faceVals[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

// Constructor: Initialize card with suit and value
Card::Card(const int suitVal, const int faceVal)
{
	setSuit(suitVal);
	setFace(faceVal);
}

// Destructor
Card::~Card()
{
	// No dynamic memory, so left as default
}

// Non-member operator<< overload
// Print card value and suit
ostream& operator<<(ostream& out, const Card& theCard)
{
	out << Card::faceVals[theCard.face] << " of " << Card::suits[theCard.suit] << endl;
	return out;
}

// Member operator== overload
// compares card's value together
bool Card::operator==(const Card& theCard)
{
	return (getFace() == theCard.getFace());
}

// Member assignment operator overload
// copies one card class to another
Card& Card::operator=(const Card& theCard)
{
	suit = theCard.getSuit();
	face = theCard.getFace();
	return *this;
} 

// Set function
// validate and sets card suit 
void Card::setSuit(const int suitVal)
{
	if(suitVal < 0 || suitVal > 3)
	{
		throw invalid_argument("Invalid card suit.");
	}
	suit = suitVal;
}

// Get function
// return suit as int
int Card::getSuit() const
{
	return suit;
}

//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

// Set function
// validate and set card value
void Card::setFace(const int faceVal)
{
	if(faceVal < 0 || faceVal > 12)
	{
		throw invalid_argument("Invalid face value.");
	}
	face = faceVal;
}

// Get function
// return face as int
int Card::getFace() const
{
	return face;
}

// not sure, looks complicated
int Card::getBlackjackValue()
{
	int tempFace = face + 1;
	if(tempFace > 10)
	{
		tempFace = 10;
	}
	return tempFace;
}
