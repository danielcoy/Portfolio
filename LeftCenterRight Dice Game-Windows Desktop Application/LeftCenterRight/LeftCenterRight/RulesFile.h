#pragma once
#include "stdafx.h"

//#include <list>
#using<system.dll>
using namespace System;
using namespace System::IO;
using namespace std; 


ref class RulesFile
{
private:
	//Memeber variable for the file name
	String^ fileName; 
	//Stream Writer obect to write to file
	StreamWriter^ fileWriter;
	//Stream reader object to read from file
	StreamReader^ fileReader;
	//Member variable for the number of lines in the file
	int numLines; 

	//Function to count the number of lines in the file
	void CountLines();
	//Function to display the line to the screen
	void Display(String^ line);

		
public:
	RulesFile(String^ fileName);
	void ReadAndDisplay(System::Windows::Forms::TextBox^ textbox);
	String^ GetFileInfo();

};

