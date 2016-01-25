//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef CARDGAME_H
#define CARDGAME_H

#include "Card.h"
#include "Player.h"
#include "CasinoGame.h"
#include <vector>
class CardGame: public CasinoGame
{
public:
	explicit CardGame(const int = 1, const int = 1);
	virtual ~CardGame();
	static const int NUM_CARDS = 52;
	
protected:
	virtual void deal() = 0;
	virtual void playHuman(const int) = 0;
	virtual void gameAI(const int) = 0;
	virtual void reset() = 0;
	void createDeck();
	void shuffle();
	std::vector<Card> deck;
	std::vector<Card> * playerHands;
};

#endif
