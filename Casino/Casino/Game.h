//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#ifndef GAME_H
#define GAME_H
#include "Player.h"

class Game {
public:
	Game();
	virtual ~Game();
	virtual void play(Player &) = 0;
};

#endif GAME_H