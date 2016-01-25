//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "Craps.h"//includes definition of Craps
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<Player> Players;//creates a vector of players to track players

Craps::Craps()
	:quit('n')
{
}

//playing the game
void Craps::play(Player &player)
{
	cout << "Welcome to craps"<<endl; //greeting
	Players.resize(0);
	cout << "Please enter player name: ";//getting intial players name
	cin >> name;
	addPlayer(name);
	Players.at(0).setBalance(player.getBalance());
	while(quit != 'y' && quit != 'Y')
	{
		cout << "\nNew Round!\n\nPlayers make your bets.\n\n";

		for(int i =0; i<Players.size(); i++  )
		{
		
			cout << Players.at(i).getName() << " current balance: " <<Players.at(i).getBalance() <<"\nselect bet amount: "; //allows player to select bet amount
			cin >> betAmount;
			if (betAmount>Players.at(i).getBalance())//ensures the bet is valid
			{
				betAmount = Players.at(i).getBalance();
				cout << "Exceeded max bet: " << Players.at(i).getBalance() << endl;
			}
			Players.at(i).debitPlayer(betAmount);//debits the players chip stack
			int Type;
			
			//get bet type
			cout << "Enter bet Type"
			"\n1 for Pass line"
			"\n2 for don't Pass line: ";

			cin >> Type;
			Players.at(i).setBetType(Type);//sets the bet type to track win or lose
		}
		
		winner();
		char leave;
		char newplayer;
		cout << "Does a player want to join?(y or n) ";
		cin >> newplayer;

		while(newplayer=='y')//allows players to join after plays till a max of 8 players
		{
			if(Players.size() >= 8)
			{
				cout << "Table full, no more players can join.\n";
				newplayer = 'n';
			}
			else{
				cout << "Please enter player name: ";
				cin >> name;
				addPlayer(name);
				cout << "Does another player want to join?(y or n) ";
				cin >> newplayer;
			}
		}
		for(int i =1; i<Players.size(); i++  )//allows players to leave table 
		{
			cout << Players.at(i).getName() << ", want to leave table?(y or n) ";
			cin >> leave;
			if(leave == 'y')
			{
				removePlayer(Players.at(i).getName());
				i = i-1;
			}
		}
		cout << "\nDo you want to quit craps?(y or n) ";
		cin >> quit;
	}

	player.setBalance(Players.at(0).getBalance());

}//end function that plays the game

//add a player to the game
void Craps::addPlayer(string name)
{
	Players.push_back(Player(name));//adds a new player to the table
}//end function add player

//remove player from the player list
void Craps::removePlayer(string name)
{
	for(int i =0; i<Players.size(); i++  )
	{
		if( Players.at(i).getName() == name )
		{
		  Players.erase(Players.begin()+i);
		    
		}
	}
}//end funtion remove player


//looking for winner
void Craps::winner()
{
	
		
			aDie Ca, Ba;
		//pass line game rules
			int point, win=0, result;
			int push = 0;
			int x,y;
			x=Ca.roll(); //rolls Die Ca
			y=Ba.roll(); //rolls Die Ba
			result = x + y; // sums Ba and Ca
			
		
			if ((result == 7 )||(result == 11))
			{
				cout<<"\nThe roll was " << result << endl;
				win = 1; //if the result is 7 or 11 the game returns 1 
			}
			else if(result == 12)//if 12 pass line loses dont pass is pushed
			{
				cout<<"\nThe roll was " << result << endl;
				win = 2;
				push = 1;
			}

			else if ((result == 2)||(result == 3))
			{
				cout<<"\nThe roll was " << result << endl;
				win = 2; //if the result is 2 3 or 12 the game returns 2 
			}
			else
			{	
				cout<<"\nThe roll was " << result << " and point has been set\n" << endl;
				point = result; //else the result is a point and must be rerolled
				x=Ca.roll(); //rolls Die Ca
				y=Ba.roll(); //rolls Die Ba
				result = x + y; // sums Ca and Ba
				cout<<"\nThe roll was " << result << endl;
				if(result ==point)
				{
					cout<<"\nThe Point has been hit." << endl;
					win = 1;
				}
				while((result != point) && (result != 7)) //rerolls till the player rolls the point or 7
				{
					x=Ca.roll(); //rolls Die Ca
					y=Ba.roll(); //rolls Die Ba
					result = x + y; // sums Ca and Ba
					cout<<"\nThe roll was " << result<<endl;
					if (result == 7)
					{
						win = 2;
						cout<<"\nPoint has been broken." << endl;

					}
					else if(result == point)
					{
						cout<<"\nThe Point has been hit." << endl;
						win=1;
					}
					else 
						result = result;
				}
			}

		for(int i =0; i<Players.size(); i++  )
		{
			if (Players.at(i).getBetType()==1)//checks if winner of pass line
			{
				if(win == 1)
				{
					Players.at(i).creditPlayer(betAmount*2);
					cout << Players.at(i).getName() << " Has won! new balance: " << Players.at(i).getBalance() << endl;
				}
				else
				{
					cout << Players.at(i).getName() << " Has lost=[ new balance: " << Players.at(i).getBalance() << endl;
				}
			}
			else if (Players.at(i).getBetType() == 2)//checks if winner of dont pass line
			{
				if((win == 2)&&(push==1))
				{
					
					Players.at(i).creditPlayer(betAmount);
					cout << Players.at(i).getName() << "'s bet was pushed."<< endl;
				}
				else if(win == 2)
				{
					
					Players.at(i).creditPlayer(betAmount*2);
					cout << Players.at(i).getName() << " Has won! new balance: " << Players.at(i).getBalance() << endl;
				}
				else
				{
					cout << Players.at(i).getName() << " Has lost=[ new balance: " << Players.at(i).getBalance() << endl;
				}
			}
			
		}

		

}//end function determine win 

//get bet amount
double Craps::getBetAmount()
{
	return betAmount;
}//end funtion get bet amount

//destructor
Craps::~Craps()
{
}//end function destructor