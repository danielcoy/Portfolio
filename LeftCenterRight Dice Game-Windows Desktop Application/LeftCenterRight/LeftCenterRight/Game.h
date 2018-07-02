#pragma once
#include "stdafx.h"


//Include my classes
#include "RulesFile.h"
#include "Dice.h"
#include "Player.h"
#include "MyForm.h"

//#using<system.dll>

//using namespace System;
//using namespace System::IO;
using namespace System::Windows::Forms;

ref class Game
{
private:
	int numPlayers;
	cli::array<Player^>^ playerArray; 
		
	String^ userInput;

//	System::Windows::Forms::TextBox^ textbox; 

//	LeftCenterRight::MyForm^ form; 
				
	//Determine the player to the left, and pass a chip
	void PassChipLeft(int currentPlayer);
	//Determine the player to the right and pass a chip
	void PassChipRight(int currentPlayer);
	//Pass a chip to the center
	void PassChipCenter(int currentPlayer);
	//Determine if the game should continue or should end
	bool ContinueGame();
	//Prompt the user and get input
	void GetUserInput();
	//Display the current scores to the screen
	void DisplayScore(int currentPlayer);
	
	
	
public:
	//Constructor
	Game();
	//Run the main game loop
	void RunGame();
	void InitGame(); 
	

};
