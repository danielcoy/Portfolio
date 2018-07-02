#include "stdafx.h"
#include "Player.h"

//Contructor
Player::Player(String^ name)
	:playerName(name)
	,numChips(3), textBoxName(name)
{
}

//Set the player name to the parameter
void Player::SetName(String^ name)
{
	playerName = name;
}

//Return the player name string
String^ Player::GetName()
{
	return playerName; 
}

//Return the Text Box Name
String^ Player::GetTextBoxName()
{
	return textBoxName;
}

//Set the number of chips the player has
void Player::SetNumChips(int chips)
{
	numChips = chips; 
}

//Return the number of chips
int Player::GetNumChips()
{
	return numChips;
}

//Pass a chip by subtracting 1 from numChips
void Player::PassChip()
{
	numChips--; 
}

//Receive a chip by adding 1 to numChips
void Player::ReceiveChip()
{
	numChips++; 
}

//Return the number of rolls the player gets this turn based on the number of chips they have
int Player::GetNumRolls()
{
	//If they have more than 3 chips, they get 3 rolls. 
	if (numChips > 3)
	{
		return 3;
	}

	//Else if they have between 0 & 3 chips, they get that number of rolls
	else if (numChips >= 0 && numChips <= 3)
	{
		return numChips;
	}

	//Else, they have negative chips, which shouldn't ever happen, but in case it does, they get 0 rolls
	else
		return 0; 
}