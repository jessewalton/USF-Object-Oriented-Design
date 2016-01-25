//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "TexasHoldEm.h"

using namespace std;

TexasHoldEm::TexasHoldEm(const int players)
: CardGame(players, MAX_PLAYERS), cardNum(0)
{

}

TexasHoldEm::~TexasHoldEm()
{
	
}



void TexasHoldEm::sortSuits()
{
	for(int x = 0; x < combinedHand.size(); x++)
	{
		for(int y = 0; y < combinedHand.size(); y++)
		{
			if(combinedHand.at(x).getSuit() < combinedHand.at(y).getSuit())
			{
				Card temp = combinedHand.at(y);
				combinedHand.at(y) = combinedHand.at(x);
				combinedHand.at(x) = temp;
			}
		}
	}
}

void TexasHoldEm::sortRanks()
{
	for(int x = 0; x < combinedHand.size(); x++)
	{
		for(int y = 0; y < combinedHand.size(); y++)
		{
			if(combinedHand.at(x).getFace() < combinedHand.at(y).getFace())
			{
				Card temp = combinedHand.at(y);
				combinedHand.at(y) = combinedHand.at(x);
				combinedHand.at(x) = temp;
			}
		}
	}
}

int TexasHoldEm::enforceRuleSet(const int pos) const
{
	return 1;
}

void TexasHoldEm::determineConditions(const int pos)
{
	unsigned short threeOf = 0, fourOf = 0;
	unsigned short numSuccessive = 0, duplicateSuits = 0, straight = 0, flush = 0, rStraight = 0;
	short numPairs = 0;
	int endOfStr = 0, startOfStr = 0;
	bool ace = false;
	for(int x = 0; x < communityPool.size(); x++)
	{
		combinedHand.push_back(communityPool.at(x));
	}
	for(int x = 0; x < playerHands[pos].size(); x++)
	{
		combinedHand.push_back(playerHands[pos].at(x));
	}
	
	playerHands[pos].clear();
	sortSuits();
	for(int x = 0; x < combinedHand.size(); x++)
	{
		cout << combinedHand.at(x);
	}
	for(int x = 0; x < combinedHand.size() - 1; x++)
	{
		if(combinedHand.at(x).getSuit() == combinedHand.at(x+1).getSuit())
		{
			numSuccessive++;
			if(numSuccessive == 1)
			{
				startOfStr = x;
			}
			endOfStr = x;
		}
		else
		{
			numSuccessive = 0;
		}
		if(numSuccessive > 3)
		{
			flush++;
			playerCondition[pos] = 1;
			for(int y =startOfStr; y <= endOfStr + 1; y++)
			{
				playerHands[pos].push_back(combinedHand.at(y));
			}
			break;
		}
	}

	endOfStr = startOfStr = 0;
	sortRanks();
	
	numSuccessive = 0;
	for(int x = 0; x < combinedHand.size()-3; x++)
	{
		if(combinedHand.at(x) == combinedHand.at(x+1) && combinedHand.at(x) == combinedHand.at(x+2) 
		&& combinedHand.at(x) == combinedHand.at(x+3))
		{
			fourOf++;
			playerCondition[pos] = 2;
			playerHands[pos].push_back(combinedHand.at(x));
			playerHands[pos].push_back(combinedHand.at(x+1));
			playerHands[pos].push_back(combinedHand.at(x+2));
			playerHands[pos].push_back(combinedHand.at(x+3));
			break;
		}
	}
	if(fourOf < 1)
	{
		ace = combinedHand.at(0).getFace() == 0;
		for(int x = 0; x < combinedHand.size() - 1; x++)
		{
			if(combinedHand.at(x).getFace() == combinedHand.at(x+1).getFace() - 1)
			{
				numSuccessive++;
				if(numSuccessive == 1)
				{
					startOfStr = x;
				}
				endOfStr = x;
				if(combinedHand.at(x).getSuit() == combinedHand.at(x+1).getSuit())
				{
					duplicateSuits++;
				}
				if(combinedHand.at(x+1).getFace() == 12 && ace && numSuccessive > 2 && duplicateSuits > 2 && combinedHand.at(x+1).getSuit() == combinedHand.at(0).getSuit())
				{
					if(flush > 0)
					{
						playerHands[pos].clear();
					}
					rStraight++;
					playerCondition[pos] = 3;
					playerHands[pos].push_back(Card(0,0));
					playerHands[pos].push_back(Card(0,12));
					playerHands[pos].push_back(Card(0,11));
					playerHands[pos].push_back(Card(0,10));
					playerHands[pos].push_back(Card(0,9));
					flush = 0;
					break;
				}
				else if(numSuccessive > 2 && duplicateSuits > 2 && combinedHand.at(x+1).getSuit() == combinedHand.at(x).getSuit())
				{
					
				}
				else if(combinedHand.at(x+1).getFace() == 12 && ace && numSuccessive > 2)
				{
					if(flush > 0)
					{
						playerHands[pos].clear();
					}
					straight++;
					playerHands[pos].push_back(Card(0,0));
					playerHands[pos].push_back(Card(1,12));
					playerHands[pos].push_back(Card(2,11));
					playerHands[pos].push_back(Card(3,10));
					playerHands[pos].push_back(Card(1,9));
					playerCondition[pos] = 4;
					break;
				}
			}
			else if(combinedHand.at(x).getFace() == combinedHand.at(x+1).getFace())
			{
				continue;
			}
			else
			{
				numSuccessive = 0;
			}
			if(numSuccessive > 3)
			{
				if(flush > 0)
				{
					playerHands[pos].clear();
				}
				straight++;
				playerCondition[pos] = 4;
				for(int y =startOfStr; y <= endOfStr + 1; y++)
				{
					playerHands[pos].push_back(combinedHand.at(y));
				}
				break;
			}
		}
		if(straight < 1  && rStraight < 1)
		{
			for(int x = 0; x < combinedHand.size()-2; x++)
			{
				if(combinedHand.at(x) == combinedHand.at(x+1) && combinedHand.at(x) == combinedHand.at(x+2))
				{
					threeOf++;
					if(threeOf > 1 && playerHands[pos].at(0).getFace() != 0)
					{
						for(int x = 0; x < 3; x++)
						{
							playerHands[pos].pop_back();
						}
					}
					playerHands[pos].push_back(combinedHand.at(x));
					playerHands[pos].push_back(combinedHand.at(x+1));
					playerHands[pos].push_back(combinedHand.at(x+2));	
					playerCondition[pos] = 6;
					if(playerHands[pos].at(0).getFace() == 0)
					{
						break;
					}
				}
			}
			
			if(threeOf > 0)
			{
				numPairs-=2;
			}
			
			for(int x = 0; x < combinedHand.size()-1; x++)
			{
				if(combinedHand.at(x) == combinedHand.at(x+1))
				{
					if(flush == 1 && threeOf < 1)
					{
						break;
					}
					numPairs++;
					if(numPairs > 1 || (threeOf == 1 && numPairs == 1))
					{
						if(threeOf == 1 && numPairs == 1)
						{
							playerCondition[pos] = 7;
							continue;
						}
					}
				}
			}	
		}
	}
	
	if(numPairs > 0 && rStraight < 1 && flush < 1 && straight < 1 && 
	fourOf < 1 && threeOf < 1 )
	{
		playerCondition[pos] = (numPairs > 1) ? 8 : 9;
	}
	else if(rStraight < 1 && flush < 1 && straight < 1 && 
	fourOf < 1 && threeOf < 1 && numPairs < 1)
	{
		playerCondition[pos] = 10;
	}


// get kicker
	cout << rStraight << endl;
	cout << flush << endl;
	cout << straight << endl;
	cout << fourOf << endl;
	cout << threeOf << endl;
	cout << numPairs << endl;
	cout << playerCondition[pos] << endl;
}

void TexasHoldEm::play(Player &player)
{
	cout << "Texas Hold 'em play" << endl;
	
	while(true)
	{
		deal();
		placeBets();  // pre flop
		for(int x = 0; x < 3; x++)
		{
			communityPool.push_back(deck.at(cardNum++));
		}
		placeBets(); // flop
		communityPool.push_back(deck.at(cardNum++)); //
		placeBets();
		communityPool.push_back(deck.at(cardNum++));
		placeBets();
		processResults();
	}
	//deal();
	playerHands[0].push_back(deck.at(cardNum++));
	playerHands[0].push_back(deck.at(cardNum++));
		for(int x = 0; x < 3; x++)
		{
			communityPool.push_back(deck.at(cardNum++));
		}
		communityPool.push_back(deck.at(cardNum++));
		communityPool.push_back(deck.at(cardNum++));
	determineConditions(0);
	displayCards();
	

	system("Pause");
}

void TexasHoldEm::deal()
{
	for(int x = 0; x < numPlayers; x++)
	{
		for(int y = 0; y < 2; y++)
		{
			playerHands[x].push_back(deck.at(cardNum++));
		}
	}
}

void TexasHoldEm::placeBets()
{
	
}

void TexasHoldEm::manageBets()
{
	
}

void TexasHoldEm::playHuman(const int)
{
	
}

void TexasHoldEm::gameAI(const int)
{
	
}

void TexasHoldEm::reset()
{
	
}
	
int TexasHoldEm::getHandValue(const int) const
{
	return 1;
}
	
void TexasHoldEm::displayCards() const
{
	for(int x = 0; x < communityPool.size(); x++)
	{
		cout << communityPool.at(x);
	}
	cout << endl;
	cout << "Player" << endl;
	for(int x = 0; x < playerHands[0].size(); x++)
	{
		cout << playerHands[0].at(x);
	}
}

void TexasHoldEm::processResults() const
{
	
}
