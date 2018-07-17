//Daniel Coy
//SNHU IT-145
//Final Project: Zoo Monitoring System
//

package zoomonitoringsystem;

//Import dialog display libraries
import javax.swing.JOptionPane;
import javax.swing.JDialog;

//Public class to create and display a message in a dialog box when an alert is detected in the monitoring file
public class DialogAlert {
        
    private String alertString;     //Private String field for storing the string that will be displayed
    private String headerString;    //Private String field for storing the string to be used in the dialog's header
     
    //Default constructor
    public DialogAlert() {
        alertString = "";
        headerString = "";
    }
    
    //Overloaded constructor with parameters to set the message strings on creation
    public DialogAlert(String alertString, String headerString) {
        
        //Set the alertString field to alertString argument
        this.alertString = alertString;
        
        //Set the headerString field to headerString argument
        this.headerString = headerString;
        
        //Replace *s with  ""
        this.alertString = this.alertString.replace("*", "");
    }

    //Public method for setting the dialog box's message
    public void setAlertMsg(String alertString){

        //Set the alertString field to alertString argument
        this.alertString = alertString;
        
        //Replace *s with  ""
        this.alertString = this.alertString.replace("*", "");
        
        return;                
    }
    
    //Public method for setting the dialog box header message
    public void setHeaderMsg (String headerString) {
        
        //Set the headerString field to headerString argument
        this.headerString = headerString;
        
        return;
    }

    //Public method for displaying the dialog message
    public void displayAlert() {
        
        //Create and show a dialog box of the WARNING_MESSAGE type, with the class field alertString as the message
        JOptionPane optionPane = new JOptionPane(this.alertString, JOptionPane.WARNING_MESSAGE);       
        JDialog dialog = optionPane.createDialog(this.headerString);       
        dialog.setAlwaysOnTop(true); // to show top of all other application     
        dialog.setVisible(true); // to visible the dialog
        
        return;
    }
    
}
