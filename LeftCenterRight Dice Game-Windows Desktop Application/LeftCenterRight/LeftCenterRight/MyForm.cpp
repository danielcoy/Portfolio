#include "stdafx.h"
#include "MyForm.h"
#include "Player.h"

using namespace LeftCenterRight;

void MyForm::InitGame()
{
		
	GameMessages->Text = "Game Message";

	

	//Create a new Player array of size numPlayers
	playerArray = gcnew array<Player^>(numPlayers);

	//Create new Player objects for each index of the array
	for (int i = 1; i <= numPlayers; i++)
	{
		//Prompt user to enter name, and creat new Player object with input as argument
		//Console::Write("Enter the name of player " + (i + 1) + ": ");
		playerArray[i - 1] = gcnew Player("Player" + i);
		System::Windows::Forms::Control^ tbCtrl = GetControlRef("Player" + i);
		tbCtrl->Text = playerArray[i - 1]->GetName() + "\r\nChips: " + playerArray[i - 1]->GetNumChips();
	}

	//Reset the name input iterator and show the name entry box
	name_itr = 0;
	NameBox->Text = "Enter Player1's Name Here";
	NameBox->Show();
	NameButton->Show();
	//Hide the roll button
	Roll->Hide();

	RunGame();
}

void MyForm::RunGame()
{
	//Create the dice object with 6 sides
	Dice dice(6);

	//Used to determine if game should continue
	bool continueGame = true;

	while (continueGame)
	{
		//Each run through the while loop is a round of the game. 

		//Step through the Player array to execute each player's turn
		for (int i = 0; i < numPlayers; i++)
		{
			DisplayScore(i);

			//If the ContinueGame function indicates game is over
			if (!ContinueGame())
			{
				//Set continueName to false, so the while loop does not execute again
				continueGame = false;

				//break the for-loop
				break;
			}

			//Get the number of rolls that the current player has this turn
			int numRolls = playerArray[i]->GetNumRolls();

			//Display the current player, and the number of rolls they get
			GameMessages->Text = playerArray[i]->GetName() + " gets " + numRolls + " rolls this turn.";
			//Console::WriteLine("\n" + playerArray[i]->GetName() + " gets " + numRolls + " rolls this turn. ");

			//For each roll
			for (int n = 0; n < numRolls; n++)
			{

				//Check that the player still has chips before allowing to roll
				//If the player gets down to 0 chips during their turn, it is over
				if (playerArray[i]->GetNumChips() <= 0)
				{
					GameMessages->Text = "You're out of chips. Ending turn.";
					//Console::WriteLine("You're out of chips. Ending turn.");
					break;
				}

				GameMessages->AppendText("\r\nPress the Roll Button."); 
				//Console::WriteLine("\nPress Enter to roll.");
				//Console::ReadLine();

				//While waiting for the roll button press, go do other application events.
				while (!rollPressed)
				{
					Application::DoEvents();
				}

				//Once here, the button has been pressed, so reset the toggler
				rollPressed = false; 

				//Clear Screen and displaye scores. 
				//Console::Clear();
				DisplayScore(i);

				int roll = dice.RollsDice();

				//Draw the roll
				GameMessages->AppendText ("\r\nRoll " + (n + 1) + "\r\n" + dice.DrawDice(roll)); 
				//Console::WriteLine("Roll " + (n + 1));
				//Console::WriteLine(dice.DrawDice(roll));

				//Execute a switch statement on the dice roll
				switch (roll)
				{
					//If 1 is rolled, pass a chip to the left
				case 1:
					PassChipLeft(i);
					break;

					//If 2 is rolled, pass chip to right
				case 2:
					PassChipRight(i);
					break;

					//If 3 rolled, pass chip to center
				case 3:
					PassChipCenter(i);
					break;

				default:
					GameMessages->Text = "Don't pass any chips."; 
					//Console::WriteLine("Don't pass any chips.");
					break;
				}
			}

			/*
			Console::WriteLine("\nPress Enter to end turn.");
			Console::ReadLine();
			Console::Clear();
			*/


		}

		Application::DoEvents();

	}

	//Game has ended, display final score
	GameMessages->Text = "Final Score:"; 
	
	//TODO: Add Final Score Display********************

	/*
	//Console::WriteLine("Final Score:");
	//DisplayScore(-1);

	//if the user didn't choose to quit, then find the winner
	if (userInput != "q" && userInput != "Q")
	{
		//Check who won and display message
		for (int i = 0; i < numPlayers; i++)
		{
			//If the player has chips, then they're the winner
			if (playerArray[i]->GetNumChips() > 0)
			{
				//Display the winner's name. The user of PadLeft & PadRight consecutively helps to center the win message
				Console::WriteLine("=======================================\n"
					+ "**** " + (playerArray[i]->GetName() + " Wins!")->PadLeft(18)->PadRight(29) + " ****\n"
					+ "=======================================\n");
				break;
			}
		}
	}

	Console::WriteLine("\nPress Enter to return to menu.");
	Console::ReadLine();
	*/
}

//Function to determine the player to the right and pass a chip
void MyForm::PassChipRight(int currentPlayer)
{
	int playerToRight;

	//If the current player is anyone other that player 1
	if (currentPlayer > 0)
	{
		//Player to right us 1 down from current player
		playerToRight = currentPlayer - 1;
	}

	//else if current player IS player 1
	else if (currentPlayer == 0)
	{
		//Player to right is the last player
		playerToRight = numPlayers - 1;
	}

	//else error
	else
	{
		GameMessages->Text = "ERROR: Player to right undetermined! Passing to player 1."; 
		//Console::WriteLine("ERROR: Player to right undetermined! Passing to player 1.");
		playerToRight = 0;
	}

	//Display who's passing to who
	GameMessages->Text = "Passing one chip right from " + playerArray[currentPlayer]->GetName() + " to " + playerArray[playerToRight]->GetName() + ".";
	//Console::WriteLine("Passing one chip right from " + playerArray[currentPlayer]->GetName() + " to " + playerArray[playerToRight]->GetName() + ".");

	//Pass chip from current player to player to right
	playerArray[currentPlayer]->PassChip();
	playerArray[playerToRight]->ReceiveChip();

}

//Function to determine the player to the left and pass a chip
void MyForm::PassChipLeft(int currentPlayer)
{
	int playerToLeft;

	//If the current player is less than the last player
	if (currentPlayer < numPlayers - 1)
	{
		//Player to left is up 1 spot
		playerToLeft = currentPlayer + 1;
	}

	//else if the current player IS the last player
	else if (currentPlayer == numPlayers - 1)
	{
		//Player to right is the first player
		playerToLeft = 0;
	}

	//else ERROR
	else
	{
		GameMessages->Text = "ERROR: Player to left undetermined! Passing to player 1."; 
		//Console::WriteLine("ERROR: Player to left undetermined! Passing to player 1.");
		playerToLeft = 0;
	}

	//Display who's passing to who
	GameMessages->Text = "Passing one chip left from " + playerArray[currentPlayer]->GetName() + " to " + playerArray[playerToLeft]->GetName() + "."; 
	//Console::WriteLine("Passing one chip left from " + playerArray[currentPlayer]->GetName() + " to " + playerArray[playerToLeft]->GetName() + ".");

	//Pass chip from current player to player to left
	playerArray[currentPlayer]->PassChip();
	playerArray[playerToLeft]->ReceiveChip();
}

//Function to pass a chip to the center. 
void MyForm::PassChipCenter(int currentPlayer)
{
	//Display who's passing to who
	GameMessages->Text = "Passing one chip from " + playerArray[currentPlayer]->GetName() + " to the center."; 
	//Console::WriteLine("Passing one chip from " + playerArray[currentPlayer]->GetName() + " to the center.");
	
	//Pass chip from current player to center
	playerArray[currentPlayer]->PassChip();

}

//Function to determine if the game should continue. 
//Game is over when only 1 player has chips. Go through array 	
//and count number of players with chips. If more than one, return true.
bool MyForm::ContinueGame()
{
	
	//If the user hasn't entered to quit then check if the game's over
	int playersWithChips = 0;

	//For each player
	for (int i = 0; i < numPlayers; i++)
	{
		//If the player in the current array index has more than 0 chips
		if (playerArray[i]->GetNumChips() > 0)
		{
			//Increment the players with chips counter
			playersWithChips++;
		}
	}

	//If the players with chips counter is greater than 1, that means the game should continue. 
	if (playersWithChips > 1)
	{
		return true;
	}
	//Else the game has been won and should not continue. 
	else
	{
		return false;
	}
}

//Function to get user input to continue game
void MyForm::GetUserInput()
{
	//Prompt user to press enter to continue or q to quit
	Console::WriteLine("\nPress Enter to continue with the next\n turn or 'q' to quit the game.\n");

	//Get input
	userInput = Console::ReadLine();
	
}

//Function to display the current score
void MyForm::DisplayScore(int currentPlayer)
{
	//Get the name of the current player
	String^ name = playerArray[currentPlayer]->GetName();

	//Get the name of the current player text box
	String^ tbName = playerArray[currentPlayer]->GetTextBoxName();

	//Set the text of the current player text box to the name and number of chips
	GetControlRef(tbName)->Text = name + "\r\nChips: " + playerArray[currentPlayer]->GetNumChips();

	/*
	String^ turnIndicator = " ";

	for (int i = 0; i < numPlayers; i++)
	{
		if (i == currentPlayer)
		{
			turnIndicator = ">";
		}
		Console::WriteLine(turnIndicator + playerArray[i]->GetName()->PadRight(14) +
			Convert::ToString(playerArray[i]->GetNumChips())->PadLeft(18) + " chips");

		turnIndicator = " ";
	}
	*/
	
}
