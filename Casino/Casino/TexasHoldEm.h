//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef TEXASHOLDEM_H
#define TEXASHOLDEM_H

#include "CardGame.h"

#define SMALL_BLIND 2
#define BIG_BLIND 4

class TexasHoldEm: public CardGame
{
public:
	explicit TexasHoldEm(const int = 1);
	virtual ~TexasHoldEm();
	virtual void play(Player &);
	static const int MAX_PLAYERS = 8;
	static const std::string validInputs[4];
	
protected:
	virtual int enforceRuleSet(const int) const;
	virtual void deal();
	virtual void placeBets();
	virtual void manageBets();
	virtual void processResults() const;
	virtual void playHuman(const int);
	virtual void gameAI(const int);
	virtual void reset();
	int getHandValue(const int) const;
	void displayCards() const;
	void sortRanks();
	void sortSuits();
	void determineConditions(const int);
	std::vector<Card> communityPool;
	std::vector<Card> combinedHand;
	double completePot;
	double betAmount;
	int cardNum;
};

#endif
