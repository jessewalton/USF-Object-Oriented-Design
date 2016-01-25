//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef CRAPS_H
#define CRAPS_H

#include <string>
#include "Game.h"
#include "aDie.h"
#include "Player.h" //uses class player

using namespace std;

class Craps : public Game
{
public:
	
	Craps();
	~Craps();
	void addPlayer(string);
	void winner();
	void removePlayer(string);
	void play(Player &);
	
	double getBetAmount();

private:
	string name;
	char playerJoin, quit;
	double betAmount;
};

#endif