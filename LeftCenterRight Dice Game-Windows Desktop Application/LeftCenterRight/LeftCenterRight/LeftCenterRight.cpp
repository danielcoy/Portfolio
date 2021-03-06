// LeftCenterRight.cpp : Defines the entry point for the console application.
//

/*********************************************************************************************************
Daniel Coy
Left Center Right
2/25/2018

This program simulates the dice game Left Center Right. Details on the rules for the game are included in 
the "LCRRules.txt" file found in the program directory. These rules can also be displayed in the program. 
The program implements several classes for its key components. A Player class to manage each player and his
or her stats. A Dice class to manage the rolling and functionality of the dice in game. The RulesFile class 
is implemented to display the rules and the logo at the start of the game. Finally, the Game class contains
the main game-loop, as well as the functions to implement and manage the game rules. 

BUGS: Several bugs were encoutnered and resolved during the creation of this program. The first major bug 
encountered was during the creation of the arra of Player objects that is utilized by the Game class to
manage the players. Thet traditional systax for the creation of an array did not work in this instance,
due to the need to create the array dynamically based on the number of players, and because certain 
Visual Studio & Command Line Options(CLI) options and functionality precludes the use of String^ and
other "managed" objects in these arrays. After some additional research using MSDN and Stack Overflow, the 
correct syntax was implemented. I also used some test code to ensure it was functioning as intended 
before continuing further with development. 

When creating the functions to Pass to the Right and Pass to the Left, it was discovered that they were 
passing in the opposite direction than they should be. This was a relatively easy fix, just changing around
the calculations, but it required the use of the debugger to track down where the issue was. 

While testing the game, and having other people play it as well, I discovered a bug that occurred when the
user entered the quit command ("q" or "Q"). I wanted to implement a check so that when the user chooses 
to quit, the winner message is NOT displayed. Otherwise, the game would show a winner even if the game
was not complete. This check is done by a simple if-statement to make sure the user had not entered either
"q" or "Q". Originally the if-statement read if(userInput != "q" || userInput != "Q"), but this lead to 
a situation where ther if-statement ALWAYS evaluated to true, since if the input will always be not "q" 
OR not "Q". After chekcing and evaluating the logic, it was determined that the && operator was needed, 
because it needed to be neither "q" and "Q". 

Several other bugs were discovered during the process of coding. Using the method of frequent compilation
and testing, these bugs were often discovered and resolved quickly. By compiling and testing after every
significant addition or change, I was able to determine if an issue with the new code existed, and correct
it before it became more difficult to track down. 
**********************************************************************************************************/

#include "stdafx.h"

//Include my classes
#include "RulesFile.h"
#include "Dice.h"
#include "Game.h"

/***************************************************/
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
/*************************************************/


/**************** Original Main method and show logo & rules methods.**************************
*****************These are being transitioned over to button functions.************************


//Functions to show the rules & logo from files
void ShowRules();
void ShowLogo(); 

//Main
int main()
{
	//Input String
	String^ userInput = " ";
	
	while (userInput != "3")
	{
		Console::Clear();

		//Display the logo
		ShowLogo();

		//Prompt user and get menu selection. 
		Console::WriteLine("\nEnter your selection and press enter: \n1. Play Game \n2. Show Rules \n3. Quit");
		userInput = Console::ReadLine();
		
		//If input 1, run game
		if (userInput == "1")
		{
			//Create Game object and start the game
			Game LCRGame;
			LCRGame.RunGame();
		}

		//If 2, show the ruls
		else if (userInput == "2")
		{
			Console::Clear();
			//Show the game rules
			ShowRules();
		}
		
		//If 3, exit game
		else if (userInput == "3")
		{
			//Prompt user to press enter before closing the program
			Console::WriteLine("\nPress Enter to exit.");
			Console::ReadLine();
		}

		//Otherwise, invalid input
		else
		{
			Console::WriteLine("\n Invalid input. Press enter to return.");
			Console::ReadLine();
			userInput = " "; 
		}
	}
		
    return 0;
}

//Function to show the rules frome a file

void ShowRules()
{
	//RulesFile rules("LCRRules.txt");
	//rules.ReadAndDisplay();
	
	//Console::WriteLine("\nPress Enter to return to menu.");
	//Console::ReadLine();
}

//Function to show the logo from a file. 
void ShowLogo()
{
	//RulesFile logo("LCRLogo.txt");
	//logo.ReadAndDisplay(); 

}
*/

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	LeftCenterRight::MyForm form;

	Application::Run(%form);
		
		
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
