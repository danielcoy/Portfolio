#include "stdafx.h"
#include "RulesFile.h"


//Constructor with the filename as paramater. 
RulesFile::RulesFile(String^ fileName)
	:fileName(fileName)
	, numLines(0)
{
	//Try to open the file with the fileReader object
	try
	{
		fileReader = File::OpenText(fileName);
	}

	//Catch the exceptions
	catch (Exception^ e)
	{
		//If the exception is that no file is found
		if (dynamic_cast<FileNotFoundException^>(e))
		{
			Console::WriteLine("The '{0}' file was not found. An empty file has been created.", fileName);
			//Use the fileWriter object to create the file
			fileWriter = gcnew StreamWriter(fileName, true);
			//Close file
			fileWriter->Close();
			//Now open it with the fileReader
			fileReader = File::OpenText(fileName);
		}
		else
		{
			Console::WriteLine("Problem reading file {0}", fileName);
		}
	}

	CountLines();
}

//Method for reading in the file line by line, and displaying it to the screen 
//Reference to the textbox that will display the text as argument
void RulesFile::ReadAndDisplay(System::Windows::Forms::TextBox^ textbox)
{
	//String to hold the line read in 
	String^ lineIn;
	
	//while the line being read in does not equal a null pointer
	while ((lineIn = fileReader->ReadLine()) != nullptr)
	{
		//Add the line to the textbox's text
		textbox->Text += lineIn + "\r\n";
		//Previously called Display() function to write to console
		//Display(lineIn);

	}

	return;
}

//Method to dispay the line to the screen
void RulesFile::Display(String^ line)
{
	Console::WriteLine(line);

	return;
}

//Method to count the number of lines in the file. This 
void RulesFile::CountLines()
{
	//While there is a next line, increment num lines
	while ((fileReader->ReadLine()) != nullptr)
	{
		numLines++;
	}

	//Close & reopn the file
	fileReader->Close();
	fileReader = File::OpenText(fileName);

	return;
}

//Method to return a string with the file's info. 
String^ RulesFile::GetFileInfo()
{
	String^ info = "File '" + fileName + "' is being displayed and contains " + numLines + " lines."; 
	return info;
}
