#pragma once

//#using<system.dll>
#include "RulesFile.h"
#include "Player.h"
#include "Dice.h"

#using<system.dll>


namespace LeftCenterRight {
	

	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		public:
			MyForm(void) : numPlayers(0), name_itr(0)
			{
				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//

				//Hide all the player text boxes
				this->Player1->Hide();
				this->Player2->Hide();
				this->Player3->Hide();
				this->Player4->Hide();
				this->Player5->Hide();
				this->Player6->Hide();
				this->NameBox->Hide();
				this->NameButton->Hide();

				//Open logo text file and dispay in the textbox
				RulesFile logo("LCRLogo.txt");
				logo.ReadAndDisplay(this->textBox1);
			}
					
		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MyForm()
			{
				if (components)
				{
					delete components;
				}
			}
	
		private: System::Windows::Forms::Button^  PlayGame;
		private: System::Windows::Forms::TextBox^  textBox1;
		private: System::Windows::Forms::Button^  Quit;
		private: System::Windows::Forms::Button^  Roll;
		private: System::Windows::Forms::Button^  ShowRules;
	private: System::Windows::Forms::ComboBox^  NumPlayersCombo;

		private: System::Windows::Forms::TextBox^  Player1;
		private: System::Windows::Forms::TextBox^  Player2;
		private: System::Windows::Forms::TextBox^  Player3;
		private: System::Windows::Forms::TextBox^  Player4;
		private: System::Windows::Forms::TextBox^  Player5;
		private: System::Windows::Forms::TextBox^  Player6;
		private: System::Windows::Forms::TextBox^  GameMessages;
	private: System::Windows::Forms::TextBox^  NameBox;

	private: System::Windows::Forms::Button^  NameButton;

		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container ^components;

			#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->PlayGame = (gcnew System::Windows::Forms::Button());
				this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				this->Quit = (gcnew System::Windows::Forms::Button());
				this->Roll = (gcnew System::Windows::Forms::Button());
				this->ShowRules = (gcnew System::Windows::Forms::Button());
				this->NumPlayersCombo = (gcnew System::Windows::Forms::ComboBox());
				this->Player1 = (gcnew System::Windows::Forms::TextBox());
				this->Player2 = (gcnew System::Windows::Forms::TextBox());
				this->Player3 = (gcnew System::Windows::Forms::TextBox());
				this->Player4 = (gcnew System::Windows::Forms::TextBox());
				this->Player5 = (gcnew System::Windows::Forms::TextBox());
				this->Player6 = (gcnew System::Windows::Forms::TextBox());
				this->GameMessages = (gcnew System::Windows::Forms::TextBox());
				this->NameBox = (gcnew System::Windows::Forms::TextBox());
				this->NameButton = (gcnew System::Windows::Forms::Button());
				this->SuspendLayout();
				// 
				// PlayGame
				// 
				this->PlayGame->Location = System::Drawing::Point(12, 495);
				this->PlayGame->Name = L"PlayGame";
				this->PlayGame->Size = System::Drawing::Size(75, 25);
				this->PlayGame->TabIndex = 0;
				this->PlayGame->Text = L"Play Game";
				this->PlayGame->UseVisualStyleBackColor = true;
				this->PlayGame->Click += gcnew System::EventHandler(this, &MyForm::PlayGame_Click);
				// 
				// textBox1
				// 
				this->textBox1->AcceptsReturn = true;
				this->textBox1->AllowDrop = true;
				this->textBox1->Location = System::Drawing::Point(12, 12);
				this->textBox1->Multiline = true;
				this->textBox1->Name = L"textBox1";
				this->textBox1->ReadOnly = true;
				this->textBox1->Size = System::Drawing::Size(958, 300);
				this->textBox1->TabIndex = 1;
				// 
				// Quit
				// 
				this->Quit->Location = System::Drawing::Point(12, 553);
				this->Quit->Name = L"Quit";
				this->Quit->Size = System::Drawing::Size(75, 25);
				this->Quit->TabIndex = 2;
				this->Quit->Text = L"Quit";
				this->Quit->UseVisualStyleBackColor = true;
				this->Quit->Click += gcnew System::EventHandler(this, &MyForm::Quit_Click);
				// 
				// Roll
				// 
				this->Roll->Location = System::Drawing::Point(400, 495);
				this->Roll->Name = L"Roll";
				this->Roll->Size = System::Drawing::Size(200, 50);
				this->Roll->TabIndex = 3;
				this->Roll->Text = L"Roll";
				this->Roll->UseVisualStyleBackColor = true;
				this->Roll->Click += gcnew System::EventHandler(this, &MyForm::Roll_Click);
				// 
				// ShowRules
				// 
				this->ShowRules->Location = System::Drawing::Point(12, 524);
				this->ShowRules->Name = L"ShowRules";
				this->ShowRules->Size = System::Drawing::Size(75, 25);
				this->ShowRules->TabIndex = 4;
				this->ShowRules->Text = L"Show Rules";
				this->ShowRules->UseVisualStyleBackColor = true;
				this->ShowRules->Click += gcnew System::EventHandler(this, &MyForm::ShowRules_Click);
				// 
				// NumPlayersCombo
				// 
				this->NumPlayersCombo->AllowDrop = true;
				this->NumPlayersCombo->FormattingEnabled = true;
				this->NumPlayersCombo->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"3", L"4", L"5", L"6" });
				this->NumPlayersCombo->Location = System::Drawing::Point(897, 495);
				this->NumPlayersCombo->Name = L"NumPlayersCombo";
				this->NumPlayersCombo->Size = System::Drawing::Size(75, 21);
				this->NumPlayersCombo->TabIndex = 5;
				this->NumPlayersCombo->Text = L"# Players";
				this->NumPlayersCombo->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::NumPlayers_SelectedIndexChanged);
				// 
				// Player1
				// 
				this->Player1->AcceptsReturn = true;
				this->Player1->AllowDrop = true;
				this->Player1->Location = System::Drawing::Point(12, 12);
				this->Player1->Multiline = true;
				this->Player1->Name = L"Player1";
				this->Player1->ReadOnly = true;
				this->Player1->Size = System::Drawing::Size(150, 300);
				this->Player1->TabIndex = 6;
				// 
				// Player2
				// 
				this->Player2->AcceptsReturn = true;
				this->Player2->AllowDrop = true;
				this->Player2->Location = System::Drawing::Point(174, 12);
				this->Player2->Multiline = true;
				this->Player2->Name = L"Player2";
				this->Player2->ReadOnly = true;
				this->Player2->Size = System::Drawing::Size(150, 300);
				this->Player2->TabIndex = 7;
				// 
				// Player3
				// 
				this->Player3->AcceptsReturn = true;
				this->Player3->AllowDrop = true;
				this->Player3->Location = System::Drawing::Point(334, 12);
				this->Player3->Multiline = true;
				this->Player3->Name = L"Player3";
				this->Player3->ReadOnly = true;
				this->Player3->Size = System::Drawing::Size(150, 300);
				this->Player3->TabIndex = 8;
				// 
				// Player4
				// 
				this->Player4->AcceptsReturn = true;
				this->Player4->AllowDrop = true;
				this->Player4->Location = System::Drawing::Point(496, 12);
				this->Player4->Multiline = true;
				this->Player4->Name = L"Player4";
				this->Player4->ReadOnly = true;
				this->Player4->Size = System::Drawing::Size(150, 300);
				this->Player4->TabIndex = 9;
				// 
				// Player5
				// 
				this->Player5->AcceptsReturn = true;
				this->Player5->AllowDrop = true;
				this->Player5->Location = System::Drawing::Point(658, 12);
				this->Player5->Multiline = true;
				this->Player5->Name = L"Player5";
				this->Player5->ReadOnly = true;
				this->Player5->Size = System::Drawing::Size(150, 300);
				this->Player5->TabIndex = 10;
				// 
				// Player6
				// 
				this->Player6->AcceptsReturn = true;
				this->Player6->AllowDrop = true;
				this->Player6->Location = System::Drawing::Point(820, 12);
				this->Player6->Multiline = true;
				this->Player6->Name = L"Player6";
				this->Player6->ReadOnly = true;
				this->Player6->Size = System::Drawing::Size(150, 300);
				this->Player6->TabIndex = 11;
				// 
				// GameMessages
				// 
				this->GameMessages->AcceptsReturn = true;
				this->GameMessages->AllowDrop = true;
				this->GameMessages->Location = System::Drawing::Point(300, 318);
				this->GameMessages->Multiline = true;
				this->GameMessages->Name = L"GameMessages";
				this->GameMessages->ReadOnly = true;
				this->GameMessages->Size = System::Drawing::Size(400, 50);
				this->GameMessages->TabIndex = 12;
				// 
				// NameBox
				// 
				this->NameBox->Location = System::Drawing::Point(401, 442);
				this->NameBox->Name = L"NameBox";
				this->NameBox->Size = System::Drawing::Size(135, 20);
				this->NameBox->TabIndex = 13;
				this->NameBox->TextChanged += gcnew System::EventHandler(this, &MyForm::NameBox_TextChanged);
				// 
				// NameButton
				// 
				this->NameButton->Location = System::Drawing::Point(550, 443);
				this->NameButton->Name = L"NameButton";
				this->NameButton->Size = System::Drawing::Size(50, 20);
				this->NameButton->TabIndex = 14;
				this->NameButton->Text = L"Enter";
				this->NameButton->UseVisualStyleBackColor = true;
				this->NameButton->Click += gcnew System::EventHandler(this, &MyForm::NameButton_Click);
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(984, 586);
				this->Controls->Add(this->NameButton);
				this->Controls->Add(this->NameBox);
				this->Controls->Add(this->GameMessages);
				this->Controls->Add(this->Player6);
				this->Controls->Add(this->Player5);
				this->Controls->Add(this->Player4);
				this->Controls->Add(this->Player3);
				this->Controls->Add(this->Player2);
				this->Controls->Add(this->Player1);
				this->Controls->Add(this->NumPlayersCombo);
				this->Controls->Add(this->ShowRules);
				this->Controls->Add(this->Roll);
				this->Controls->Add(this->Quit);
				this->Controls->Add(this->textBox1);
				this->Controls->Add(this->PlayGame);
				this->Name = L"MyForm";
				this->Text = L"Daniel Coy: LeftCenterRight";
				this->ResumeLayout(false);
				this->PerformLayout();

			}
		#pragma endregion
	
		///////////////////////////////Add Functions to MyForm Class here///////////////////////////////////////////////////
		
			//Number of players
		private:
			int numPlayers;
			int name_itr;
			bool rollIsPressed = false;
			array<Player^>^ playerArray;
			

			String^ userInput;
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
			void RunGame();
			void InitGame();
			
///////////////////////////////////////////////////////////////////////////////////////////
			//Set TextBox Text Functions
			void SetText(String^ text)
			{

				this->textBox1->Text = text;

			}
			//Set text from an external source
			void SetExternalText(String^ text)
			{
				SetText(text);
			}

			//Add text, but keep what's already displayed
			void AddText(String^ text) {

				this->textBox1->AppendText(text);

			}

			//Clear the text
			void ClearText()
			{
				this->textBox1->Clear();
			}
			////////////////////////////////////////////////

			System::Windows::Forms::Control^ GetControlRef(String^ name)
			{
				array<System::Windows::Forms::Control^>^ ctrl = this->Controls->Find(name, true);

				return ctrl[0];
			}


///////////////////////////////////////////////////////////////////Button Clicks////////////////////////////////////////////////////////////////////
		private: 
		
			//PlayGame Button Click
			System::Void PlayGame_Click(System::Object^  sender, System::EventArgs^  e) 
			{
			
														
				try
				{
					//String to hold the selected item from the player # drop down
					String^ snum = NumPlayersCombo->SelectedItem->ToString();
					
					//Set text to the selected item
					//SetText(snum);
					
					//Convert the selected item to an integer	
					numPlayers = int::Parse(snum);
							
																			
				}

				//Catch all exceptions that are thrown if the number of players is not selected
				catch (...)
				{
					MessageBox::Show("Number of Players not selected. Defaulting to 3.");
					NumPlayersCombo->SelectedIndex = 0;
					numPlayers = 3;
				}

				//Hide the main text box
				this->textBox1->Hide();
				//Hide all the player text boxes
				this->Player1->Hide();
				this->Player2->Hide();
				this->Player3->Hide();
				this->Player4->Hide();
				this->Player5->Hide();
				this->Player6->Hide();

				//For the number of players currently selected, go through and show those text boxes. 
				for (int i = 1; i <= numPlayers; i++)
				{
					String^ name = "Player" + i;
					ShowTextbox(name);
				}

				InitGame();
						
			}
	
		//QUIT button click
		private: 
			System::Void Quit_Click(System::Object^  sender, System::EventArgs^  e) 
			{
				//Close the form
				this->Close();
			}

		//Roll button click
		private: 
			System::Void Roll_Click(System::Object^  sender, System::EventArgs^  e) 
			{
				//toggle the roll is pressed bool
				rollIsPressed = !rollIsPressed;

				
			}
		//Show Rules Button
		private: 
			System::Void ShowRules_Click(System::Object^  sender, System::EventArgs^  e) 
			{
				//Clear the display
				ClearText();

				//Open the rules file and display the text
				RulesFile rules("LCRRules.txt");
				rules.ReadAndDisplay(this->textBox1);
			}

		//NumPlayers selected change
		private:
			System::Void NumPlayers_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
			{

			}

		private: 
			void ShowTextbox(String^ name)		
			{
				array<System::Windows::Forms::Control^>^ ctrl = this->Controls->Find(name, true); 
				ctrl[0]->Show();

			}
			




		private: System::Void NameButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			//If the current name iterator value is less that the number of players
			if (name_itr < numPlayers)
			{
				//Set the name of the player to the value in the text box
				playerArray[name_itr]->SetName(this->NameBox->Text);
				
			//	String^ tbn = playerArray[name_itr]->GetTextBoxName(); 
				
				//Set the name in the appropriate player text box
				DisplayScore(name_itr);

				//iterate name counter and set the text to prompt from next player. 
				name_itr++;
				this->NameBox->Text = "Enter Player" + (name_itr + 1) + "'s Name";
			}

			//When the iterater is greater than or equal to the number of players, hide the box & button
			if (name_itr >= numPlayers)
			{
				this->NameBox->Hide();
				this->NameButton->Hide();
			}
		}
	

		private: System::Void NameBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		}


	};//End of Class Def
}//End of Namespace
