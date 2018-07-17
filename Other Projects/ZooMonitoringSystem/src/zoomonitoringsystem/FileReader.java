//Daniel Coy
//SNHU IT-145
//Final Project: Zoo Monitoring System
//

package zoomonitoringsystem;

//Import Scanner library for input scanning
import java.util.Scanner;
//Import file import packages
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    
    private String fileName;       //Private field for storing the name of the file to read from
    private String userInput;      //Private field for storing the user's input
    private String menuOptions;    //Private field for storing the menu options to be displayed to user
    private String fileType;       //Private field for storing the file type, e.g. "animal" or "habitat"
    private int dataSetLength;     //Private field to store the length of the file's data set, 
                                   //i.e. num lines per entry. 5 for animals, 4 for habitat
    private int numDataSets;       //Private field for the number of data sets in the file
    private String fileData[][];   //Private field for storing the file's data into an array
    
    private FileInputStream fileStream; //File input stream
    private Scanner fileScanner;        //file scanner object
    
    //Default constructor
    public FileReader() throws IOException {
        //initialize the fields
        this.fileName = "";
        this.userInput = "";
        this.menuOptions = "";
        this.fileType = "";
        this.dataSetLength = 0;
        this.numDataSets = 0;
        
        //initialize the file stream and scanner
        fileStream = new FileInputStream(fileName);
        fileScanner = new Scanner(fileStream);        
    }
    
    //Overloaded constructor with file name and data set length as parameters
    public FileReader(String fileName, int dataSetLength) throws IOException {
        
        //set the fileName field to the argument
        this.fileName = fileName;
        //set the dataSetLength field to the argument
        this.dataSetLength = dataSetLength;
        
        //Initialize other strings for use
        this.userInput = "";
        this.menuOptions = "";
        this.fileType = "";
        
        //initialize the file stream and scanner
        fileStream = new FileInputStream(fileName);
        fileScanner = new Scanner(fileStream);
        
        //Set the numDataSets field by calling the helper method
        this.numDataSets = getNumDataSets();
        
        //String to hold the nextline read in the file
        String nextLine = "";
        
        //Read the next line in the file, and while that line contains 
        //"Details" append that animal onto the menuOptions string
        nextLine = fileScanner.nextLine();
                    
        while(nextLine.contains("Details")) {
            this.menuOptions = this.menuOptions.concat(" | " + nextLine.substring(11));
            nextLine = fileScanner.nextLine();            
        }
        
        //Add "return" to menu options
        this.menuOptions = this.menuOptions.concat(" | return |");
        //Make menuOptions all caps
        this.menuOptions = this.menuOptions.toUpperCase();

        //Initialze the fileData array with size numDataSets by dataSetLength
        //This will provide a row for each data set in the file, and a comlumn for each line of that data set
        this.fileData = new String[this.numDataSets][this.dataSetLength];
                 
        //While the file has a next line to read, step through dataSetLength number of lines at a time
        // and store those in the array
        int i = 0; //loop counter
        while (fileScanner.hasNextLine()) {
            
            //if the next line is not "". This prevents empty lines being stored in the array
            if (!nextLine.equals("")){
                //FOR loop to step through the next dataSetLength number of lines and store in each column of row i
                for (int n = 0; n < dataSetLength; n++) {
                    this.fileData[i][n] = nextLine;

                    //if the file has a nextLine, get it
                    if (fileScanner.hasNextLine()){
                        nextLine = fileScanner.nextLine();
                    }
                }
                
                //When done with all columns in the row, iterate i to move to the next row
                i++;
            }
            
            else {
                nextLine = fileScanner.nextLine();
            }
            
        }
           
    }
    
    //Private helper method to count the number of data sets in the file
    private int getNumDataSets() throws IOException {
        
        //Open the file and initialize a stream and scanner
        FileInputStream getSetsScanner = new FileInputStream(fileName);
        Scanner scnr = new Scanner(getSetsScanner);
        
        int numSets = 0;    //number of data sets in the file
        String nextLine = ""; //Holds the scanned nextLine
        this.fileType = fileName.replace("s.txt", "").toLowerCase(); //Remove the "s.txt" from the file name 
                                                                       // to get the file type i.e. animal or habitat
                                                                       // and convert to lowercase 
        
        //Loop through each line in the file, if the line containns fileType (ignoring case),
        //then it is a data set, so increment numSets
        
        //While the file has a next line
        while (scnr.hasNextLine()) {
            //Get the next line
            nextLine = scnr.nextLine();
            //convert nextLine to all lowercase
            nextLine = nextLine.toLowerCase();
            
            //If nextLine contains fileType plus " -", then it is a new data set, so increment numSets
            if (nextLine.contains(this.fileType + " -")) {
                ++numSets;
            }
        }
        
        //close the file
        getSetsScanner.close();
        
        //return the number of data sets counted
        return numSets;      
    }
    
    //Public method to display the user's selection to the screen 
    public void displaySelection(String userInput) {
           
        //convert to upper case for comparisons
        this.userInput = userInput.toUpperCase();
        
        //if userInput is not found in the menu options, then display error
        if (!this.menuOptions.contains(this.userInput)){
                System.out.println("\nSelection not valid.");
           }
        
        //else, display the selection
        else {
            //Step through each row and column of the fileData array
            //If the first column in a row contains the user input, then display that whole row
            for (int i = 0; i < numDataSets; i++) {

                //get the string index of the "-" character in the line
                int dashIndex = this.fileData[i][0].indexOf("-");
                
                //if the user input contains the substring starting after the "-" + 2 (where the type of animal/habitat starts
                if (this.userInput.contains(this.fileData[i][0].substring(dashIndex + 2).toUpperCase())) {
                    System.out.println("");
                    //display all the columns by stepping through each one
                    for (int n = 0; n < dataSetLength; n++){
                        System.out.println(this.fileData[i][n]);
                        
                        //if the line contains the alert string, then display alert dialog
                        if(this.fileData[i][n].contains("*****")) {
                                DialogAlert animalAlert = new DialogAlert(this.fileData[i][n], 
                                                                        "!!! " + this.fileType.toUpperCase() + " ALERT!!!");
                                animalAlert.displayAlert();
                        }
                    }
                }
            }
        }
    }
    
    //Public method to return the menu options list
    public String getMenuOptions () {
        return menuOptions;
    }
}
