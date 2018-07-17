package com.example.daniel.contractiontimer;


import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;


public class DisplayContractionLog extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_contraction_log);

        //Call the display log method
        try {
            displayLog();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    //Public method for displaying the contents of the log
    public void displayLog() throws IOException{

        String fileOutput = "";

        //String to hold the file name
        String filename = "contractionLog.txt";

        //Create a new File object for the contractionLog file
        File file = new File(getFilesDir(), filename);

        //Create a file input stream to read from the file
        FileInputStream inputStream = new FileInputStream(file);

        //Scanner for the inputStream
        Scanner scnr = new Scanner(inputStream);

        //While there is a next line in the file
        while (scnr.hasNextLine()) {
            //Advance the scanner passed the current line
            String nextLine = scnr.nextLine();

            //If the next line has "Stop" then add a newline
            if (nextLine.substring(0, 4) == "Stop"){
            nextLine += "\n";
            }

            //Add the new line to the string
            fileOutput = fileOutput + nextLine;



        }

        inputStream.close();


        //Write the string retrieved from the file to the TextView
        TextView contractionLog = (TextView) findViewById(R.id.textView_ContractionLog);


        contractionLog.setText(fileOutput);

    }



}
