//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "Blackjack.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

const string Blackjack::validInputs[4] = {"hit", "stand", "double down", "surrender"};
static int handNumber = 1;

Blackjack::Blackjack(const int players)
: CardGame(players + 1, MAX_PLAYERS + 1), cardNum(0), dealerBust(false)
{

}

Blackjack::~Blackjack()
{
	
}

int Blackjack::getHandValue(const int pos) const
{
	int score = 0;
	int numAces = 0;
	for(int x = 0; x < playerHands[pos].size(); x++)
	{
		int val = playerHands[pos].at(x).getBlackjackValue();
		if(val == 1)
		{
			numAces++;
		}
		score += val;
	}
	for(int x = 0; x < numAces; x++)
	{
		if(score + 10 <= 21)
		{
			score += 10;
		}
	}
	return score;
}

int Blackjack::enforceRuleSet(const int pos) const
{
	int score = getHandValue(pos);
	
	if(score > 21)
	{
		return 0;
	}
	else if(score < 21)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void Blackjack::play(Player &player)
{

	players.at(1).setBalance(player.getBalance());
	cout << players.at(1).getBalance() << endl;

	bool play = true;
	while(play)
	{
		placeBets();
		deal();
		cout << "\nDealer has " << playerHands[0].at(0);
		displayCards();
		for(int x = 1; x < numPlayers; x++)
		{
			if(players.at(x).getHumanity())
			{
				playHuman(x);
			}
			else
			{
				gameAI(x);
			}
		}
		
		cout << "\nDealer completes their hand with " << playerHands[0].at(1);
		
		while(getHandValue(0) < 17)
		{
			Card temp = deck.at(cardNum++);
			cout << "Dealer hits." << endl;
			playerHands[0].push_back(temp);
			cout << temp;
		}
		cout << endl;
		
		processResults();
		manageBets();
		
		cout << "Continue playing? (Y/N)";
		string userIn;
		
		while(play)
		{
			getline(cin, userIn);
			if(userIn.compare("Y") == 0)
			{
				deck.clear();
				for(int x = 0; x < numPlayers; x++)
				{
					playerHands[x].clear();
				}
				cardNum = 0;
				createDeck();
				shuffle();
				break;
			}
			else if(userIn.compare("N") == 0)
			{
				play = false;
		
			}
			else
			{
				cout << "Invalid input. Continue playing? (Y/N)";
			}
		}
	}
	player.setBalance(players.at(1).getBalance());
}

void Blackjack::deal()
{
	for(int x = 0; x < 2; x++)
	{
		for(int y = 1; y < numPlayers; y++)
		{
			playerHands[y].push_back(deck.at(cardNum++));
		}
		playerHands[0].push_back(deck.at(cardNum++));
	}
}

void Blackjack::placeBets()
{
	string input;
	//srand(time(0));
	for(int x = 1; x < numPlayers; x++)
	{
		if(players.at(x).getHumanity())
		{
			cout << "Please enter a bet amount between $5 and $100: ";
			while(true)
			{
				try
				{
					getline(cin, input);
					validateBet(input, x);
				}
				catch(invalid_argument& ex)
				{
					cerr << ex.what();
					continue;
				}
				cout << players.at(x).getName() << " bets $" << playerBets[x] << "!" << endl;
				break;
			}
		}
		else
		{
			playerBets[x] = (rand() % 16) + 5;
			cout << players.at(x).getName() << " bets $" << playerBets[x] << "!" << endl;
		}
	}
}

void Blackjack::validateBet(string& input, const int pos)
{
	int decCount = 0;
	double testAmount = 0;
	for(int x = 0; x < input.length(); x++)
	{
		if(!isdigit(input[x]) && decCount++ == 0 && input[x] != '.')
		{
			throw invalid_argument("Invalid bet amount. Please enter a bet amount between $5 and $100: ");
		}
	}
	testAmount = atof(input.c_str());
	if(testAmount < 5 || testAmount > 100)
	{
		throw invalid_argument("Invalid bet amount. Please enter a bet amount between $5 and $100: ");
	}
	playerBets[pos] = testAmount;
}

void Blackjack::manageBets() // Implement correct payouts
{
	for(int x = 1; x < numPlayers; x++)
	{		
		if(playerCondition[x] == 0)
		{
			cout << players.at(x).getName() << " lost!" << endl;
			players.at(x).debitPlayer(playerBets[x]);
		}
		else if(playerCondition[x] == 1)
		{
			cout << players.at(x).getName() << " outscored the dealer!" << endl;
			players.at(x).creditPlayer(playerBets[x]);
		}
		else if(playerCondition[x] == 2)
		{
			cout << players.at(x).getName() << " got a Blackjack!" << endl;
			players.at(x).creditPlayer(playerBets[x] * 1.5);
		}
		else
		{
			cout << players.at(x).getName() << " surrendered for hand!" << endl;
			players.at(x).debitPlayer(playerBets[x]/2);
		}
		//cout << getHandValue(x) << endl;
		cout << players.at(x).getName() << "'s balance: $"<<players.at(x).getBalance() << "\n" <<endl;
	}
}

void Blackjack::processResults() const
{
	int dealerScore = getHandValue(0);
	int splitOrig = 0;
	if(enforceRuleSet(0) == 0)
	{
		cout << "\nDEALER BUST!\n" << endl;
	}
	else if(enforceRuleSet(0) == 2 && playerHands[0].size() < 3)
	{
		cout << "\nDEALER BLACKJACK!\n" << endl;
	}
	for(int x = 1; x < numPlayers; x++)
	{
		if(enforceRuleSet(0) == 0 && playerCondition[x] < 3)
		{
			playerCondition[x] = (enforceRuleSet(x) == 1) ? 1 : playerCondition[x];
			playerCondition[x] = (enforceRuleSet(x) == 2 && playerHands[x].size() < 3) ? 2 : playerCondition[x];
			playerCondition[x] = (enforceRuleSet(x) == 2 && playerHands[x].size() >= 3) ? 1 : playerCondition[x];
		}
		else if(enforceRuleSet(0) == 1 && playerCondition[x] < 3)
		{
			playerCondition[x] = (enforceRuleSet(x) == 1 && getHandValue(x) > getHandValue(0)) ? 1 : playerCondition[x];
			playerCondition[x] = (enforceRuleSet(x) == 2 && playerHands[x].size() < 3 && getHandValue(x) >= getHandValue(0)) ? 2 : playerCondition[x];
			playerCondition[x] = (enforceRuleSet(x) == 2 && playerHands[x].size() >= 3 && getHandValue(x) >= getHandValue(0)) ? 1 : playerCondition[x];
		}
		else if(enforceRuleSet(0) == 2 && playerCondition[x] < 3)
		{
			playerCondition[x] = 0;
		}
	}
}

void Blackjack::displayCards() const
{
	for(int x = 1; x < numPlayers; x++)
	{
		cout << "\n" << players.at(x).getName() << "'s Cards\n" << endl;
		for(int y = 0; y < playerHands[x].size(); y++)
		{
			cout << playerHands[x].at(y);
		}
	}
}

void Blackjack::gameAI(const int pos)
{
	srand(time(0));
	int daring = rand() % 31;
	int numActions = 0;
	while(enforceRuleSet(pos) == 1)
	{
		if(getHandValue(pos) < 18 || playerHands[pos].size() < 2)
		{
			Card newCard = deck.at(cardNum++);
			playerHands[pos].push_back(newCard);
			if(enforceRuleSet(pos) < 1)
			{
				cout << players.at(pos).getName() << " got busted!" << endl;
				playerCondition[pos] = 0;
				handNumber--;
				break;
			}
		}
		else if(getHandValue(pos) <= 16 && daring > 5)
		{
			Card newCard = deck.at(cardNum++);
			playerHands[pos].push_back(newCard);
			if(enforceRuleSet(pos) < 1)
			{
				cout << players.at(pos).getName() << " got busted!" << endl;
				playerCondition[pos] = 0;
			}
			break;
		}
		else if((getHandValue(pos) > 11 && getHandValue(pos) < 15) && numActions == 0 && daring < 8)
		{
			playerCondition[pos] = 3;
			break;
		}
		else
		{
			playerCondition[pos] = 1;
			break;
		}
		numActions++;
	}
}

void Blackjack::playHuman(const int pos)
{
	int numActions = 0;
	string userIn;
	while(enforceRuleSet(pos) == 1)
	{
		cout << "\nEnter play for hand (in lowercase, no spaces): ";
		getline(cin, userIn);
		if(userIn.compare(validInputs[0]) == 0)
		{
			Card newCard = deck.at(cardNum++);
			playerHands[pos].push_back(newCard);
			cout << newCard;
			if(enforceRuleSet(pos) < 1)
			{
				cout << "Busted!" << endl;
				playerCondition[pos] = 0;
				break;
			}
		}
		else if(userIn.compare(validInputs[1]) == 0)
		{
			playerCondition[pos] = 1;
			break;
		}
		else if(userIn.compare(validInputs[2]) == 0)
		{
			playerBets[pos] *= 2;
			Card newCard = deck.at(cardNum++);
			playerHands[pos].push_back(newCard);
			cout << newCard;
			if(enforceRuleSet(pos) < 1)
			{
				cout << "Busted!" << endl;
				playerCondition[pos] = 0;
				break;
			}
			break;
		}
		else if(userIn.compare(validInputs[3]) == 0 && numActions == 0)
		{
			playerCondition[pos] = 3;
			break;
		}
		else
		{
			cout << "Invalid play.";
			continue;
		}
		numActions++;
	}
}

void Blackjack::reset()
{
	for(int x = 1; x < numPlayers; x++)
	{
		if(players.at(x).getBalance() <= 0)
		{
			players.at(x).creditPlayer(1000);
		}
	}
	vector<Card> * newHands = new vector<Card>[numPlayers];
	double * newBets = new double[numPlayers];
	int * newConditions = new int[numPlayers];
	delete playerHands;
	delete playerBets;
	delete playerCondition;
	playerHands = newHands;
	playerBets = newBets;
	playerCondition = newConditions;
}
