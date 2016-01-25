//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef CASINOGAME_H
#define CASINOGAME_H

#include "Game.h"
#include "Player.h"
#include <vector>
class CasinoGame : public Game
{
public:
	explicit CasinoGame(const int = 1, const int = 1);
	virtual ~CasinoGame();
	virtual void play(Player &) = 0;
	
protected:
	virtual int enforceRuleSet(const int) const = 0;
	virtual void placeBets() = 0;
	virtual void manageBets() = 0;
	virtual void processResults() const = 0;
	void initializePlayers();
	std::string name;
	std::vector<Player> players;
	double * playerBets;
	int * playerCondition;
	int numPlayers;
};

#endif
