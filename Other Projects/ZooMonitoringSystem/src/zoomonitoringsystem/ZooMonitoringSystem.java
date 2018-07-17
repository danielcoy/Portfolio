//Daniel Coy
//SNHU IT-145
//Final Project: Zoo Monitoring System
//

package zoomonitoringsystem;

//Import Scanner library for input scanning
import java.util.Scanner;
import java.io.IOException;

public class ZooMonitoringSystem {
    
    public static void main(String[] args) throws IOException {
        
        Scanner scnr = new Scanner(System.in);  //Input scanner
        String userInput = "";                  //User input string
        
        //Display monitoring system header
        System.out.println("*************************************************************" + 
                         "\n********SOUTHERN NEW HAMPSHIRE ZOO MONITORING SYSTEM*********" + 
                         "\n*************************************************************");
        
        //While the user input does not equal "exit" continue to ask for menu selection
        while (!userInput.equalsIgnoreCase("exit")) {
                                  
            //Display menu selections
            System.out.print("Monitor ANIMAL, HABITAT, or EXIT?"
                             + "\nSelection: ");
            
            //Get the user's input
            userInput = scnr.nextLine();
            
            //If the input is "animal" then call animal monitoring method
            if (userInput.equalsIgnoreCase("animal")) {
                AnimalMonitoring();
            }
            
            //Else if input is "habitat" call habitat monitoring method
            else if (userInput.equalsIgnoreCase("habitat")) {
                HabitatMonitoring();
            }
            
            //Else if input is "exit" display exit message
            else if (userInput.equalsIgnoreCase("exit")) {
                System.out.println("\n*************************************************************"
                                 + "\n****************EXITING ZOO MONITORING SYSTEM****************"
                                 + "\n*************************************************************");
            }
            
            //else input is invalid, display error message
            else {
                System.out.println("Invalid Input");
            }
        }
    }
    
     //Animal Monitoring Method
    public static void AnimalMonitoring() throws IOException {
                
        Scanner scnr = new Scanner(System.in);          //System input scanner
        String userInput = "";  //String to hold user input
        String menuOptions = "";//String to hold menu options list
        
        //Create a new FileReader object and initialize with animals.txt
        FileReader animalsFileReader = new FileReader("animals.txt", 5);
        
        //set menuOptions string
        menuOptions = animalsFileReader.getMenuOptions();
        
        //Provide user with options, and prompt for input
        System.out.println("\n*************************************************************" + 
                           "\n******************ANIMAL MONITORING SYSTEM*******************" +
                           "\n*************************************************************");
        System.out.println("Enter animal(s) you wish to monitor from the list below. "
                         + "\nType 'return' to return to main menu." );
                        
        //While the user's input does not equal "return", continue to ask for a selection
        while (!userInput.equalsIgnoreCase("return")) {
            
            //Output menu options string
            System.out.println("\n" + menuOptions);
             //Ask for and get selection
            System.out.print("\nSelection: ");
            userInput = scnr.nextLine();
            
            //call FileReader display method with userInput as argument
            animalsFileReader.displaySelection(userInput);
            
            //Print new line
            System.out.println("");
            
       }
             
        System.out.println("*************************************************************" 
                       + "\n**************EXITING ANIMAL MONITORING SYSTEM***************"
                       + "\n*******************RETURNING TO MAIN MENU********************"
                       + "\n*************************************************************");
                         
        return;
    }
    
    //Habitat Monitoring Method
    public static void HabitatMonitoring() throws IOException{
        
        Scanner scnr = new Scanner(System.in);          //System input scanner
        String userInput = "";  //String to hold user input
        String menuOptions = "";//String to hold menu options list
        
        //Create a new FileReader object and initialize with animals.txt
        FileReader habitatsFileReader = new FileReader("habitats.txt", 4);
        
        //set menuOptions string
        menuOptions = habitatsFileReader.getMenuOptions();
        
        //Provide user with options, and prompt for input
        System.out.println("\n*************************************************************" + 
                           "\n*****************HABITAT MONITORING SYSTEM*******************" +
                           "\n*************************************************************");
        System.out.println("Enter habitat(s) you wish to monitor from the list below. "
                         + "\nType 'return' to return to main menu.");
                        
        //While the user's input does not equal "return", continue to ask for a selection
        while (!userInput.equalsIgnoreCase("return")) {
            
            //Output menu options string
            System.out.println("\n" + menuOptions);
             //Ask for and get selection
            System.out.print("\nSelection: ");
            userInput = scnr.nextLine();
            
            //call FileReader display method with userInput as argument
            habitatsFileReader.displaySelection(userInput);
            
            //Print new line
            System.out.println("");
            
       }
             
        System.out.println("*************************************************************" +
                         "\n**************EXITING HABITAT MONITORING SYSTEM**************"
                       + "\n*******************RETURNING TO MAIN MENU********************"
                       + "\n*************************************************************");
                         
        return;
    }

}
