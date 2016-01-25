//
//  Final Project - Casino
//
//  Jesse Walton
//  Tim Flippen
//  Ryan Kurtz
//

#include "SlotMachine.h"
#include "RandomNumber.h"
#include "Player.h"

#include <iomanip>

RandomNumber NumberGenerator(0, 9);

SlotMachine::SlotMachine()
{
    
}

SlotMachine::~SlotMachine()
{

}

void SlotMachine::play(Player &player)
{
	int menuSelect = 0;
	bool continueLoop = true;
	int bet = 0;
	static int run = 0;

	while (continueLoop)
	{
		if (run++ == 0)
		{
			buildMachine(player); // just for show to build display
		}

		if (processInput(bet))
		{
			spin(bet, player);
		}
		else
		{
			continueLoop = false;
			run = 0;
		}
	}
}

void SlotMachine::spin(int bet, Player &player) //spin reels, calculate win, adjust balance accordingly
{
	system("CLS");

	bool win = false;
	
	int winnings = 0;

	static int row[3][3] = { 1, 1, 1, 2, 2, 2, 3, 3, 3 };

	string symbols[10] = {
		"Horseshoe   ", "Diamond    ", "Spade     ", "Heart     ", "Bell      ",
		"Cherry     ", "Coin      ", "Star      ", "Clover     ", "Bar      " };

	// deduct bet amount from player balance
	player.debitPlayer(bet);

	line();
	line("SLOT MACHINE");
	line();

	// Generate wheel positions for next spin
	for (int k = 0; k < 3; k++)
	{
		row[0][k] = NumberGenerator.generate();
		row[1][k] = ((row[0][k] + 1) % 10);
		row[2][k] = ((row[0][k] + 2) % 10);
		NumberGenerator.generate();
		NumberGenerator.generate();
	}


	// display wheels
	for (int r = 0; r < 3; r++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "| ";
			cout << setw(14) << symbols[row[r][i]];
		}
		cout << " |";
		cout << endl;
	}
	line();
	spacerLine();


	// detect win

	// check 3 like symbols in center row
	if ((row[1][0] == row[1][1]) && (row[1][0] == row[1][2]))
	{
		line("WINNER    -  3 IN A ROW  -    WINNER");
		win = true;
		player.creditPlayer(bet * 300);
		winnings = 300;
	}

	// check if 2 like symbols in center row
	
	else if ((row[1][0] == row[1][1]) || (row[1][0] == row[1][2]) || (row[1][1] == row[1][2])) 
	{
		line("WINNER    -  2 IN A ROW  -    WINNER");
		win = true;
		player.creditPlayer(bet * 30);
		winnings = 30;
	}
	
	else
	{

		// count frequency of symbols
		int frequency[10] = { 0 };

		for (int num = 0; num < 10; num++)
		{
			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					if (row[x][y] == num)
					{
						frequency[num]++;
					}
				}
			}
		}


		// check for 3 matching symbols on the screen
		for (int count = 0; count < 10; count++)
		{
			if (frequency[count] == 3)
			{
				line("WINNER   - 3 SYMBOL MATCH -   WINNER");
				win = true;
				player.creditPlayer(bet * 5);
				winnings = 5;
				break;
			}
		}


		// check for 2 matching symbols on the screen
		if (!win)
		{
			for (int count = 0; count < 10; count++)
			{
				if (frequency[count] == 2)
				{
					line("WINNER   - 2 SYMBOL MATCH -   WINNER");
					win = true;
					player.creditPlayer(bet * 2);
					winnings = 2;
					break;
				}
			}
		}
	}

	if (!win)
	{
		line("YOU  LOSE!");
	}

	spacerLine();
	buildMenu(player.getBalance(), bet, winnings*bet);

}

bool SlotMachine::processInput(int &bet)
{
	int menuSelect = 0;
	//bool go = true;

	while (1)
	{
		cout << "\nSelection: ";
		cin >> menuSelect;

		switch (menuSelect)
		{
		case 1:
			bet = 1;
			return true;
			break;

		case 2:
			bet = 2;
			return true;
			break;

		case 5:
			bet = 5;
			return true;
			break;

		case 10:
			bet = 10;
			return true;
			break;

		case 0:
		case 'x':
		case 'X':
			return false;
			break;
		}
	}
}

void SlotMachine::buildMachine(Player &player) // display machine's initial state
{
	system("CLS"); // clear screen

	line();
	line("SLOT MACHINE");
	line();

	// display wheels
	for (int r = 0; r < 3; r++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "| ";
			cout << setw(14) << "XXXXXXX    ";
		}
		cout << " |";
		cout << endl;
	}
	line();
	spacerLine();
	line("");
	spacerLine();

	buildMenu(player.getBalance());
}

void SlotMachine::buildMenu(int balance)
{
	cout << "+--------------------------+--+------------------+" << endl;
	cout << "|  Player Options          |  |   Player Stats   |" << endl;
	cout << "+-----+--------------------+--+------------------+" << endl;
	cout << "|     |                    |  |                  |" << endl;
	cout << "|  1  |  Bet 1 dollars     |  |  Bet:         0  |" << endl;
	cout << "|  2  |  Bet 2 dollars     |  |                  |" << endl;
	cout << "|  5  |  Bet 5 dollars     |  |  Win:         0  |" << endl;
	cout << "| 10  |  Bet 10 dollars    |  |                  |" << endl;
	cout << "|     |                    |  |  Balance: " << setw(5) << balance << "  |" << endl;
	cout << "|  0  |   Exit to Menu     |  |                  |" << endl;
	cout << "+-----+--------------------+--+------------------+" << endl;
}

void SlotMachine::buildMenu(int balance, int bet, int winnings)
{
	cout << "+--------------------------+--+------------------+" << endl;
	cout << "|  Player Options          |  |   Player Stats   |" << endl;
	cout << "+-----+--------------------+--+------------------+" << endl;
	cout << "|     |                    |  |                  |" << endl;
	cout << "|  1  |  Bet 1 dollars     |  |  Bet:     " << setw(5) << bet		<< "  |" << endl;
	cout << "|  2  |  Bet 2 dollars     |  |                  |" << endl;
	cout << "|  5  |  Bet 5 dollars     |  |  Win:     " << setw(5) << winnings << "  |" << endl;
	cout << "| 10  |  Bet 10 dollars    |  |                  |" << endl;
	cout << "|     |                    |  |  Balance: " << setw(5) << balance	<< "  |" << endl;
	cout << "|  0  |   Exit to Menu     |  |                  |" << endl;
	cout << "+-----+--------------------+--+------------------+" << endl;
}

void SlotMachine::line() // generic line, width of menu
{
	for (int y = 0; y < 50; y++)
	{
		if (y % 49 == 0)
			cout << "+";
		else
			cout << "-";
	}
	cout << endl;
}

void SlotMachine::line(string text) // center text on line with end brackets
{
	string line = "+------------------------------------------------+";

	int fill = (line.length() - text.length())/2;

	cout << "|";

	for (int y = 0; y < fill - 1; y++)
	{
		cout << " ";
	}

	cout << text;

	for (int y = 0; y < fill - 1; y++)
	{
		cout << " ";
	}

	cout << "|" << endl;
}

void SlotMachine::spacerLine() // blank line with end brackets
{
	for (int y = 0; y < 50; y++)
	{
		if (y % 49 == 0)
			cout << "|";
		else
			cout << " ";
	}
	cout << endl;
}