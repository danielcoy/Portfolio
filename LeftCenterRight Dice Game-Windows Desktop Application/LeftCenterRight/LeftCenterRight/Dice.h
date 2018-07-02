#pragma once

#include "stdafx.h"

#using<system.dll>

using namespace System;

ref class Dice
{

private: 
	int numSides; 

public:
	//Constructor
	Dice(int sides);
	//Set the number of sides that the dice has
	void SetNumSides(int sides);
	//Get and return the number of sides
	int GetNumSides();
	//Roll the dice and return the results
	int RollsDice(); 
	//Return a string that represents an image of the roll
	String^ DrawDice(int roll);

};

