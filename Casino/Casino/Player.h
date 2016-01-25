#ifndef PLAYER_H
#define PLAYER_H

//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include <string>

#define INIT_BAL 1000
#define MAX_NAME_LENGTH 15

class Player
{
public:
	explicit Player(const std::string& = NULL, const bool = false);
	~Player();
    
	template <typename A> void creditPlayer(A amount);
	template <typename B> void debitPlayer(B amount);
	void setName(const std::string&);
	std::string getName() const;
	double getBalance() const;
	void setBalance(double);
	bool getHumanity() const;
	bool operator==(const Player&);
	static const std::string defaultNames[8];
	//static const int MAX_NAME_LENGTH;
	//static const double INIT_BAL;
    int getBetType();
	void setBetType(int);
	
private:
	std::string name;
	double balance;
	bool isHuman;
    int betType;
};

//const int Player::MAX_NAME_LENGTH = 15;
//const double Player::INIT_BAL = 1000;

#endif