#pragma once

#include "stdafx.h"

#using<system.dll>  
using namespace System;
using namespace System::IO;

ref class Player
{
private: 
	String^ playerName; 
	String^ textBoxName;
	int numChips; 

public:
	//Constructor
	Player(String^ name);
	//Set the player's name
	void SetName(String^ name);
	//Get and return the player's name
	String^ GetName(); 
	//Get the textBoxName
	String^ GetTextBoxName();
	//Set the number of chips that the player had
	void SetNumChips(int chips); 
	//Get and return the current number of chips 
	int GetNumChips(); 
	//Remove a chip from player
	void PassChip(); 
	//Add a chip to player
	void ReceiveChip(); 
	//Get the number of rolls player had based on number of chips
	int GetNumRolls(); 
};

