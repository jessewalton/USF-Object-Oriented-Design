//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "CardGame.h"
#include <string>
#include <vector>

class Blackjack: public CardGame
{
public:
	explicit Blackjack(const int = 1);
	virtual ~Blackjack();
	virtual void play(Player &);
	static const int MAX_PLAYERS = 5;
	static const std::string validInputs[4];
	
protected:
	void validateBet(std::string&, const int);
	virtual void playHuman(const int);
	virtual void gameAI(const int);
	virtual int enforceRuleSet(const int) const;
	virtual void deal();
	virtual void placeBets();
	virtual void manageBets();
	virtual void processResults() const;
	virtual void reset();
	int getHandValue(const int) const;
	void displayCards() const;
	bool dealerBust;
	int cardNum;
};

#endif

