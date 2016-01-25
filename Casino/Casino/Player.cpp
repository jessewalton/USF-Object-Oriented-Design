//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "Player.h"
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

const string Player::defaultNames[8] = {"Sarah", "Jon", "Ryan", "Jesse", "Tim", "Liza", "Rachel", "Sam"};

Player::Player(const string& playerName, const bool human)
:balance(INIT_BAL), isHuman(human)
{
	setName(playerName);
}

Player::~Player()
{
	// No dynamic memory, so left as default
}

template <class A> void Player::creditPlayer(A amount)
{
	balance += amount;
}
template void Player::creditPlayer(int);
template void Player::creditPlayer(double);

template <class B> void Player::debitPlayer(B amount)
{
	if (balance - amount < 0)
	{
		cout << "Balance too low" << endl;
		balance = 0;
	}
	else
	{
		balance -= amount;
	}
}
template void Player::debitPlayer(int);
template void Player::debitPlayer(double);

void Player::setName(const string& playerName)
{
	if(playerName.length() > MAX_NAME_LENGTH)
	{
		throw invalid_argument("Name has exceeded 15 character limit. Please enter a name:");
	}
	for(int x = 0; x < playerName.length(); x++)
	{
		if(!isalnum(playerName[x]))
		{
			throw invalid_argument("Invalid name. Please enter a name:");
		}
	}
	name = playerName;
}

string Player::getName() const
{
	return name;
}

double Player::getBalance() const
{
	return balance;
}

void Player::setBalance(double amount)
{
	balance = amount;
}

bool Player::getHumanity() const
{
	return isHuman;
}

void Player::setBetType(int type)
{
	betType = type;
}

int Player::getBetType()
{
	return betType;
}

bool Player::operator==(const Player& other)
{
	return (balance == other.getBalance() && name.compare(other.getName()) == 0);
}