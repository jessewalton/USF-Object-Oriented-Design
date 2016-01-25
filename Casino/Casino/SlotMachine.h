//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

// 3 reels, 10 symbols each
// Horseshoe, diamond, spade, heart, bell
// cherry, coin, star, clover, bar

// WIN CONDITIONS
// 3 matching symbols in row 1 - 300x 
// 2 matching symbols in row 1 - 30x
// 3 matching symbols in any row - 5x
// 2 matching symbols in any row - 2x

class SlotMachine : public Game
{
public:
    SlotMachine();
	~SlotMachine();
	void play(Player &player);

private:
	void spin(int bet, Player &player); // spin reels, calculate win, adjust balance accordingly
	bool processInput(int &menuSelect); // read user input
	void buildMachine(Player &player); // display machine's initial state
	void buildMenu(int balance); // first buildMenu
	void buildMenu(int balance, int bet, int winnings); // subsequent buildMenu
	void line(); // generic line, width of menu
	void line(string); // center text on line with end brackets
	void spacerLine(); // blank line with end brackets

};

#endif
