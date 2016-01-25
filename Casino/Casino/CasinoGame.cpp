//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "CasinoGame.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

CasinoGame::CasinoGame(const int players, const int maxPlayers)
{
	if(players > maxPlayers || players <= 0)
	{
		throw invalid_argument("Invalid number of players.");
	}

	numPlayers = players;
	try
	{		
		playerBets = new double[numPlayers];
		for(int x = 0; x < numPlayers; x++)
		{
			playerBets[x] = 0;
		}
		
		playerCondition = new int[numPlayers];
		for(int x = 0; x < numPlayers; x++)
		{
			playerCondition[x] = 0;
		}
	}
	catch(bad_alloc& ex)
	{
		cerr << "Fatal exception occurred. Game Over!" << endl;
		exit(EXIT_FAILURE);
	}
	initializePlayers();
}

CasinoGame::~CasinoGame()
{
	delete [] playerBets;
	delete [] playerCondition;
}

void CasinoGame::initializePlayers()
{
	int humanPos = rand() % (numPlayers - 1) + 1;
	humanPos=1;
	string name;
	int defaultNamePos = 0;
	for(int x = 0; x < numPlayers; x++)
	{
		if(x == humanPos) // May move to main later...
		{
			cout << "Enter a alphanumeric name less than 15 characters with no spaces: ";
			while(true)
			{
				getline(cin, name);
				try
				{
					Player temp(name, true);
					players.push_back(temp);
				}
				catch(invalid_argument& ex)
				{
					cerr << ex.what();
					continue;
				}
				break;
			}
		}
		else
		{
			Player temp(Player::defaultNames[defaultNamePos++], false);
			players.push_back(temp);
		}
	}
}

