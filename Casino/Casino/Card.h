//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
class Card
{
public:
	friend std::ostream& operator<<(std::ostream&, const Card&);
	explicit Card(const int = 0, const int = 0);
	~Card();
	int getSuit() const;
	int getFace() const;
	void setSuit(const int);
	void setFace(const int);
	static const std::string suits[4];
	static const std::string faceVals[13];
	static const int NUM_SUITS = 4;
	static const int NUM_FACES = 13;
	int getBlackjackValue();
	bool operator==(const Card&);
	Card& operator=(const Card&);
	
private:
	int suit;
	int face;
};

#endif
