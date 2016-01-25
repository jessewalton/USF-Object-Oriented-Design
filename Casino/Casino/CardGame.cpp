//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "CardGame.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

CardGame::CardGame(const int players, const int maxPlayers)
:CasinoGame(players, maxPlayers)
{
	playerHands = new vector<Card>[this->numPlayers];
	createDeck();
	shuffle();
}

CardGame::~CardGame()
{
	delete [] playerHands;
}

void CardGame::createDeck()
{
	for(int x = 0; x < Card::NUM_SUITS; x++)
	{
		for(int y = 0; y < Card::NUM_FACES; y++)
		{
			Card newCard(x, y);
			deck.push_back(newCard);
		}
	}
	/*
	deck.at(0) = Card(2, 7);
	deck.at(1) = Card(2, 5);
	deck.at(2) = Card(2, 6);
	deck.at(3) = Card(2, 8);
	deck.at(4) = Card(2, 12);
	deck.at(5) = Card(1, 10);
	deck.at(6) = Card(3, 4);
	*/
}

void CardGame::shuffle()
{
	for(int x = 0; x < NUM_CARDS; x++)
	{
		for(int y = 0; y < NUM_CARDS; y++)
		{
			int newLoc = rand() % NUM_CARDS;
			Card temp = deck.at(x);
			deck.at(x) = deck.at(newLoc);
			deck.at(newLoc) = temp;
		}
	}
}
