#include "stdafx.h"
#include "Dice.h"
#include <cstdlib>
#include <ctime>

//Constructor
Dice::Dice(int sides)
	:numSides(sides)
{
	//Seed the random number generator with the current time
	srand((unsigned int)time(NULL));
}

//Function to set the number of sides of the dice object
void Dice::SetNumSides(int sides)
{
	numSides = sides; 
}

//Function to return the number of sides currently set
int Dice::GetNumSides()
{
	return numSides;
}

//Roll the dice and return a radom number between 1 and the number of sides of the dice. 
int Dice::RollsDice()
{
	return (rand() % numSides) + 1;
}

//Funtion to draw an image of the dice roll
String^ Dice::DrawDice(int roll)
{
	switch (roll)
	{
	case 1:
		return "\n _______\n|       |\n|   L   |\n|       |\n|_______|\n";

	case 2:
		return "\n _______\n|       |\n|   R   |\n|       |\n|_______|\n";

	case 3:
		return "\n _______\n|       |\n|   C   |\n|       |\n|_______|\n";

	case 4:
		return "\n _______\n|  O O  |\n|       |\n|  O O  |\n|_______|\n";

	case 5:
		return "\n _______\n|  O O  |\n|   O   |\n|  O O  |\n|_______|\n";

	case 6:
		return "\n _______\n|  O O  |\n|  O O  |\n|  O O  |\n|_______|\n";

	default:
		return "ERROR DRAWING DICE";
	}
}

