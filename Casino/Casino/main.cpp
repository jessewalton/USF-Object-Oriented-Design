//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include <iostream>
#include <time.h> // for srand seed
#include <iomanip> // for setw()
#include <cctype> // for isdigit()

#include "Player.h"
#include "RandomNumber.h"
#include "SlotMachine.h"
#include "Blackjack.h"
#include "Card.h"
#include "CardGame.h"
#include "CasinoGame.h"
#include "TexasHoldEm.h"
#include "Craps.h"

using namespace std;

/*
void slotMachine(Player &player);
void craps(Player &player);
void blackJack(Player &player);
void texasHoldEm(Player &player);
*/

int main()
{
	Player player("Player1");
	Game *GamePtr = nullptr;
    
	srand(time(0)); // seed RNG, should happen in main
	int gameSelect = 0;
	bool play = true;
    
	while (play)
	{
		system("CLS");
        
		cout << "Welcome to the casino!\n" << endl;
		cout << "Balance: " << player.getBalance() << endl;
		cout << "\nPlease select a game:" << endl;
		cout << "1 - Slot Machine" << endl;
        cout << "2 - Craps" << endl;
		cout << "3 - Blackjack" << endl;
		cout << "4 - Texas Hold'em" << endl;
        cout << "0 - Exit" << endl;
		cout << "Selection (1-4): ";
        
		cin >> gameSelect;
		cin.clear();
		cin.get();
        
		switch (gameSelect)
		{
            case 1:
				GamePtr = new SlotMachine;
                break;
                
            case 2:
				GamePtr = new Craps;
                break;
                
            case 3:
				GamePtr = new Blackjack;
                break;
                
            case 4:
				//GamePtr = new TexasHoldEm;
				//play = false;
                break;
                
            case 0:
                play = false;
                break;

			default:
				break;
		}

		if (GamePtr != nullptr && play)
		{
			GamePtr->play(player);
			delete GamePtr;
		}

		/*
		Game *GameToPlay = dynamic_cast <Game *> (GamePtr);

		if (GamePtr != nullptr)
		{
			cout << "GameToPlay is pointing to " << typeid(*GameToPlay).name() << endl;
			GamePtr->play(player);
			delete GamePtr;
		}
		*/
		
	}
}

/*
void slotMachine(Player &player)
{
	SlotMachine *SlotPtr = new SlotMachine;
	SlotPtr -> play(player);
    delete SlotPtr;
}

void craps(Player &player)
{
    Craps *CrapsPtr = new Craps;
    CrapsPtr -> play(player);
    delete CrapsPtr;
}

void blackJack(Player &player)
{
	Blackjack *BlackjackPtr = new Blackjack;
    BlackjackPtr->play(player);
    delete BlackjackPtr;
}

void texasHoldEm(Player &player)
{
    TexasHoldEm *HoldemPtr = new TexasHoldEm(2); // create TexasHoldEm Class, pass 2 for number of players
    HoldemPtr->play(player);
    delete HoldemPtr;
	
}
*/