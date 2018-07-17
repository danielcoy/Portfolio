package com.example.daniel.contractiontimer;

import android.content.Context;
import android.content.Intent;
import android.icu.util.Calendar;
import android.icu.util.GregorianCalendar;

import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;


public class MainActivity extends AppCompatActivity {

    //For tracking if the button is pressed to start or stop a contraction
    public static boolean startContraction = true;

    //Array for holding contraction start and stop times
    public static long startStopTimes[][];

    public long secondsLong = 0L;
    public String newText = "";
    public String minutesLongString = "0";
    public String secondsLongString = "00";
    //Strings to hold the time apart from previous contraction
    public String lastApartMinutes = "";
    public String lastApartSeconds = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        //Initialize the start stop times array and make all values 0
        startStopTimes = new long[2][20];
        for (int i = 0; i < 2; i++) {
            for (int n = 0; n < 20; n++) {
                startStopTimes[i][n] = 0L;
            }
        }

    }


    public void onResume(){
        super.onResume();
    }

    //Called when user clicks on Start/Stop Contraction button
    @RequiresApi(api = Build.VERSION_CODES.N)
    public void startStopContraction(View view) throws IOException {

        //Get the Start/Stop button id
        Button startStop = (Button) findViewById(R.id.button_StartStop);

        //If startContaction is true it means the button has been pressed to start a contraction,
        //if it is false, then the button has been pressed to end the contraction
        //0xFFCC0000 -> dark red
        //0xff000000 -> black

        //If pressing to start a contraction
        if (startContraction) {
            //Change the font color to red
            startStop.setTextColor(0xFFCC0000);

            //Change the text, so the next press is to stop
            startStop.setText("Stop Contraction");

            //Add the start time to the startStopTimes array
            //pass 0 for a start time
            addStartStopTime(0);

            //Call the saveToLog method to write to the file
            saveToLog("Start");

            //////////////////////////////////////////////////////////////////
            //Calculate the time since the start of the last contraction//////
            //Only if there is a second contraction
            if (startStopTimes[0][1] > 0) {

                //Get the seconds apart from the latest contraction to the previous one, by subtracting the start time of the previous from the start time of latest
                Long secsApart = ((startStopTimes[0][0] - startStopTimes[0][1]) / 1000L);

                //Minutes apart equals the time apart divided by 60 to convert from seconds to minutes
                lastApartMinutes = Long.toString(secsApart / 60L);

                //if the seconds apart is less than 10, then add a leading 0. Conver milliseconds to seconds by dividing by 1000
                if ((secsApart % 60L) < 10L){
                    lastApartSeconds = "0" + Long.toString(secsApart % 60L);
                }
                //else, seconds apart is greater than 10 and does not need a leading 0
                else
                    lastApartSeconds = Long.toString(secsApart % 60L);
            }
        }
        //Else, if pressing to end a contraction
        else if (!startContraction){
            //Change the font color to green
            startStop.setTextColor(0xff669900);

            //Change the text so the next press is to start
            startStop.setText("Start Contraction");

            //Add the stop time to the startStopTimes array
            //pass 1 as parameter for a stop time
            addStartStopTime(1);

            //Call the saveToLog method to write to the file
            saveToLog("Stop");

            //The length of the contraction in seconds, is the stop time minus the start time, then divided by 1000 to convert from milliseconds to seconds.
            secondsLong = (startStopTimes[1][0] - startStopTimes[0][0]) / 1000L;

            //Minutes long, is the seconds length divided by 60.
            //This then converts it to a string for displaying
            minutesLongString = Long.toString(secondsLong / 60);

            //If the length is less that 10 seconds, then add a leading 0 to the string
            if ((secondsLong % 60) < 10)
                secondsLongString = "0" + Long.toString(secondsLong % 60);
            else
                secondsLongString = Long.toString(secondsLong % 60);

            //Call the contractionStats method to display the average stats
            //only done on the stop press, to ensure a complete contraction
            contractionStats();
        }

        newText = "Your last contraction lasted: \n" + minutesLongString + ":" + secondsLongString + "\n \n"
                + "Time apart of last two contractions: \n " + lastApartMinutes + ":" + lastApartSeconds ;

        //Get the TextView ID
        TextView contractionInfo = (TextView) findViewById(R.id.textView_ContractionInfo);

        //Set the text in the text view to newText
        contractionInfo.setText(newText);

        //Flip the value of startContraction
        startContraction = !startContraction;

    }

    //Method for adding the time the button is pressed to the startStopTimes array, and ensuring it is arranged properly. Also calls the method to save the time to the log file
    @RequiresApi(api = Build.VERSION_CODES.N)
    public void addStartStopTime(int arrayColumn) throws IOException {   //Parameter is 0 if the button is pressed at the start of a contraction, 1 if it's to stop. This will be used for the correct array column

        // create  temp array to hold values for sorting
        long tempArray[][];
        tempArray = new long[2][20];

        //If, this is a start contraction press, then a new row will need to be started, and the array sorted
        if (arrayColumn == 0) {
            //set tempArray equal to startStopTimes array
            for (int i = 0; i < 2; i++) {
                for (int n = 0; n < 20; n++) {
                    tempArray[i][n] = startStopTimes[i][n];
                }
            }
        }

        //Sorting: The new value will be placed in the 1st row of the startStopTimes array, in which ever column is indicated by arrayColumn
        //The rest of the rows will then be filled in with rows 0 - 19 of the temp array. This will cause the startStopTimes array to store
        //the most recent 20 contractions, and cause the old ones to fall off the bottom.

        //Get the current time of the button press
        startStopTimes[arrayColumn][0] = System.currentTimeMillis();

        //Only sort on new start contraction presses
        if (arrayColumn == 0) {
            //Nested for loops to step through the startStopTimes array, and assign rows 1 - 19 the values in the first 19 rows of the temp array
            for (int i = 0; i < 2; i++) {
                for (int n = 1; n < 20; n++) {
                    startStopTimes[i][n] = tempArray[i][n - 1];
                }
            }
            //Since this only occurs on new start presses, the second column in the new row needs to be re-initialized so it does not keep the old value before sorting
            startStopTimes[1][0] = 0L;
        }


    }

    //Method for calculating and displaying the running contraction stats
    public void contractionStats() {

        //Get the current time
        long currentTime = System.currentTimeMillis();

        //Go through the contraction start times, and find the first start time that is more than 3.6 million milliseconds, or 1 hour ago.
        //This will give the index for which times to use for the past hours calculations.

        int hourAgoIndex = 0;   //hold the index of the first contraction that occurred more than an hour ago.

        while ((currentTime - startStopTimes[0][hourAgoIndex]) <= 3600000L && hourAgoIndex < 19){
            hourAgoIndex++;
        }

        ////////////////////////////////////////////////////////
        //Calculate average length over past hour///////////////
        ////////////////////////////////////////////////////////
        long averageLength = 0L;    //holds the average length
        long sumLength = 0L;        //holds the sum of the lengths in order to calculate average

        //step through the array adding each contraction's length to the sum, for the contractions that occurred within last hour
        for (int i = 0; i < hourAgoIndex; i++){
            sumLength = sumLength + (startStopTimes[1][i] - startStopTimes[0][i]);
        }

        //the average equals the length sum, divided by the number of contractions that occurred in the last hour, which is the same as hourAgoIndex.
        averageLength = sumLength / hourAgoIndex;


        ////////////////////////////////////////////////////////
        //Calculate aver length of last 5 contractions//////////
        ////////////////////////////////////////////////////////
        long averageLengthFive = 0L;
        long sumLengthFive = 0L;

        //Step through the array adding each contraction's length to the sum, for the last 5 contractions
        int y = 0; //this is used to count the number of summations for finding average. Incremented each time there are actual values in the startStopTimes locations.
        for (int i = 0; i < 5; i++) {
            //Only sum if there are times actually stored in the array locations, i.e. they are > 0
            if (startStopTimes[0][i] > 0 && startStopTimes[1][i] > 0){
                y++;
                sumLengthFive = sumLengthFive + (startStopTimes[1][i] - startStopTimes[0][i]);
            }

        }

        //The average length is the sum of the last five lengths divided by 5
        averageLengthFive = sumLengthFive / y;


        //////////////////////////////////////////////////////
        //Calculate average time apart over past hour/////////
        /////////////////////////////////////////////////////
        long averageApart = 0L;     //holds the average time apart of contractions over last hour
        long apartSum = 0L;         //holds the sum of the times apart, for averaging.

        //Step through the array and add up the times between each contraction
        //Starts from the oldest contraction, located in the (hourAgoIndex - 1) row and works backward

        for (int n = hourAgoIndex - 1; n > 0; n--){
            apartSum = apartSum + (startStopTimes[0][n - 1] - startStopTimes[0][n]);
        }

        //The average equals the sum divided by the number of contractions
        averageApart = apartSum / hourAgoIndex;

        ///////////////////////////////////////////////////////
        //Calculate average time apart for last 5 contractions//
        ///////////////////////////////////////////////////////
        long averageApartFive = 0L;
        long apartSumFive = 0L;

        //Step through the array and add up the time between each contraction for the last five
        //Starts from five contractions ago and works backwards
        int x = 1; //this is used to count the number of summations for finding average. Incremented each time there are actual values in the startStopTimes locations.
        for (int n = 4; n > 0; n--) {
            //Only sum if the next time is not the default 0.
            if (startStopTimes[0][n] > 0 ){
                //increment x to track the number of summations made, in order to average
                x++;
                apartSumFive = apartSumFive + (startStopTimes[0][n - 1] - startStopTimes[0][n]);
            }

        }

        //Average equals the sum of times apart divided by 5
        averageApartFive = apartSumFive / x;



        /////////////////////////////////////////////////////
        //Convert averages to seconds and then to text///////
        /////////////////////////////////////////////////////


        //Convert the average length and time apart from milliseconds to seconds by dividing by 1000
        averageLength = averageLength / 1000L;
        averageApart = averageApart / 1000L;
        averageLengthFive = averageLengthFive / 1000L;
        averageApartFive = averageApartFive / 1000L;

        //Average Length conversion to M:SS format
        //Minutes long, is the seconds length divided by 60.
        //This then converts it to a string for displaying
        String avgMinLengthString = Long.toString(averageLength / 60);
        String avgSecondsLengthString = "";

        String avgMinLengthFiveString = Long.toString(averageLengthFive / 60);
        String avgSecondsLengthFiveString = "";

        //If the length is less that 10 seconds, then add a leading 0 to the string
        if ((averageLength % 60) < 10)
            avgSecondsLengthString = "0" + Long.toString(averageLength % 60);
        else
            avgSecondsLengthString = Long.toString(averageLength % 60);

        //Do the same with the average length of last 5 contractions
        if ((averageLengthFive % 60) < 10)
            avgSecondsLengthFiveString = "0" + Long.toString(averageLengthFive % 60);
        else
            avgSecondsLengthFiveString = Long.toString(averageLengthFive % 60);


        //Average time apart conversion to M:SS format
        //Minutes long, is the seconds length divided by 60.
        //This then converts it to a string for displaying
        String avgMinApartString = Long.toString(averageApart / 60);
        String avgSecondsApartString = "";

        String avgMinApartFiveString = Long.toString(averageApartFive / 60);
        String avgSecondsApartFiveString = "";

        //If the length is less that 10 seconds, then add a leading 0 to the string
        if ((averageApart % 60) < 10)
            avgSecondsApartString = "0" + Long.toString(averageApart % 60);
        else
            avgSecondsApartString = Long.toString(averageApart % 60);

        //Do the same with the average time apart for last 5
        if ((averageApartFive % 60) < 10)
            avgSecondsApartFiveString = "0" + Long.toString(averageApartFive % 60);
        else
            avgSecondsApartFiveString = Long.toString(averageApartFive % 60);


        //Get the TextView ID
        TextView contractionStats = (TextView) findViewById(R.id.textView_ContractionStats);
        //Set the TextView's text.

        String statsText = "Averages over last hour:\n \n"
                         + "Length:         " + avgMinLengthString + ":" + avgSecondsLengthString + "\n"
                         + "Time apart:  " + avgMinApartString + ":" + avgSecondsApartString + "\n \n"
                         + "Averages of last " + x + " contractions: \n \n"
                         + "Length:         " + avgMinLengthFiveString + ":" + avgSecondsLengthFiveString + "\n"
                         + "Time apart:  " + avgMinApartFiveString + ":" + avgSecondsApartFiveString + "\n";


        contractionStats.setText(statsText);

    }

    //Method for saving start and stop times to a log file
    @RequiresApi(api = Build.VERSION_CODES.N)
    public void saveToLog(String typeContraction) throws IOException {

        //String to hold the file name
        String filename = "contractionLog.txt";

        /*
        //Create a new File object for the contractionLog file
        File file = new File(getFilesDir(), filename);


        //Create a file input stream to read from the file
        FileInputStream inputStream = new FileInputStream(file);

        //Scanner for the inputStream
        Scanner scnr = new Scanner(inputStream);

        //Count the number of lines in the file in order to create the correct size array to hold the contents
        int x = 0;
        //While there is a next line in the file
        while (scnr.hasNextLine()) {
            //Advance the scanner passed the current line
            scnr.nextLine();
            //And count that line
            x++;
        }

        //Close input stream
        inputStream.close();

        //Create a String array of the size determined by counting the lines plus 1 more for the new line of text to be added to the file
        String logContents[] = new String[x + 1];

        //Re-open the file input stream and scanner
        inputStream = new FileInputStream(file);
        //Scanner for the inputStream
        scnr = new Scanner(inputStream);

        //Save each line of the file to a slot in the array, starting at slot 1, so that 0 is reserved for the new string to be added to the file
        x = 1;
        while (scnr.hasNextLine()){
            logContents[x] = scnr.nextLine();
            x++;
        }

        //Close input stream
        inputStream.close();
        */

        //Get current date and time and store in string.
        Calendar calendar = new GregorianCalendar();
        String currentTime = Integer.toString(calendar.get(Calendar.MONTH) + 1)  + "/"  + Integer.toString(calendar.get(Calendar.DAY_OF_MONTH)) + " " +
                Integer.toString(calendar.get(Calendar.HOUR_OF_DAY)) + ":" + Integer.toString(calendar.get(Calendar.MINUTE)) + ":" + Integer.toString(calendar.get(Calendar.SECOND)) + " \n";

        //Store the current time in slot 0 of the array
       // logContents[0] = currentTime;



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //String to be written to the file
        String stringToWrite = typeContraction + " "  + currentTime;

        //File output stream object
        FileOutputStream outputStream;

        //Opening the file output stream for the file
        outputStream = openFileOutput(filename, Context.MODE_APPEND);

        //writing the string to the file
        outputStream.write(stringToWrite.getBytes());


        //Close the file
        outputStream.close();



    }

    //Called when user clicks Contraction Log button
    @RequiresApi(api = Build.VERSION_CODES.N)
    public void contractionLog (View view)  throws IOException {
        Intent intent = new Intent(this, DisplayContractionLog.class);
        startActivity(intent);


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
