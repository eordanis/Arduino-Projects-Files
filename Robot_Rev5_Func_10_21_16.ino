/******************************************************************************
 * 
 * Tech 4440-01 FA16  10/21/16
 * Stephanie Eordanidis & Ryan Flynn
 * This program contains routines and functions to control and automate a Robot
 * This program contains racetone, stop, right turn, and straight functions
 * This program contains Test, Straight, Triangle, and Square Routines.
 * 
*******************************************************************************/
//include libraries used in program
#include <Servo.h>

//instantiate instance of servo left and right
Servo servoLeft;
Servo servoRight;

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int voltPin = 0;     // the number of the voltage pin

// variables will change:
int buttonState = 0; // variable for reading the pushbutton status
int voltState = 0;  // variable for reading the voltage status

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(voltPin, OUTPUT);

  //attach servos
  servoLeft.attach(13);
  servoRight.attach(12);

  //call stopRobot function to make servos both initially stationary
  stopRobot(); 
  
}//end setup function

// the loop function runs over and over again forever
void loop() {
  
  voltState = analogRead(voltPin); // read the state of the voltpin value
  buttonState = digitalRead(buttonPin); // read the state of the pushbutton value

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {

    //check the status of the voltage
    if(voltState >=850){
      //battery is fine, play race tone then start robot
      raceTone();
      
/******************************************************************************
 * 
 * CHOOSE WHICH ROUTINE THE ROBOT SHOULD DO AND COMMENT OUT THE REMAINING THREE
 * 
*******************************************************************************/
      startRobotStraight(); //goes straight
      //startRobotSquare();//goes in a square probably
      //startRobotTriangle(); //goes in a triangle
      //test(); //begin test function
      
    } else if(voltState <=849 && voltState >=820){
        //check to see if voltage dropped to 6v range, if so...
        //power is getting low and should be changed soon, beep twice then to alert
        tone(4, 3000, 50);
        delay(100);
        tone(4, 3000, 50);
        delay(1000);
        raceTone();   //play race tone

/******************************************************************************
 * 
 * CHOOSE WHICH ROUTINE THE ROBOT SHOULD DO AND COMMENT OUT THE REMAINING THREE
 * 
*******************************************************************************/
        startRobotStraight(); //goes straight
        //startRobotSquare();//goes in a square probably
        //startRobotTriangle(); //goes in a triangle
        //test(); //begin test function

       } else{

            //power is  low and should be changed, beep 3 times and shutdown robot
             tone(4, 3000, 50);
             delay(100);
             tone(4, 3000, 50);
             delay(100);
             tone(4, 3000, 50);
             stopRobot();
          }

  } else {

      stopRobot(); // turn servo off by calling stopRobot function
      
  }//end else if in low state

}//end loop function

/****************************************************************
 * 
 * CUSTOM FUNCTIONS START HERE AND ONLY RUN WHEN CALLED
 * 
*****************************************************************/


/*
 * function to go straight about 5 feet, write to servos
Straight Moderate Speed: 1620 L  1420 R
*/
void goStraight(int time){

    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1420);
    delay(time);
}//end goStraight

//function to stop robot by writting stopped value to servos
void stopRobot(){

    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
}//end stopRobot


/*
 * function to turn robot to the right by writting values to servos
 90 DEG TURN =>  650 DELAY
180 DEG TURN => 1300 DELAY
 45 DEG TURN =>  950 DELAY
 *
 */
void turnRobotRight(int time){

    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1500);
    delay(time);
    
}//end turnRobotRight

//function to play race start tone
void raceTone(){

    tone(4, 1000, 500); //set pizo horn
    delay(1000);
    tone(4, 1000, 500); //set pizo horn
    delay(1000);
    tone(4, 1000, 500); //set pizo horn
    delay(1000);
    tone(4, 1700, 500); //set pizo horn
    delay(1000);
}//end raceTone

//function to start robot routine
void startRobotStraight(){

    goStraight(6000);  //call goStraight function
    turnRobotRight(1300); //call turnRobotRight function
    goStraight(6000);  //call goStraight function
    stopRobot();// turn servo off by calling stopRobot function
    
}//end startRobotStraight

//function to start robot routine
void startRobotSquare(){

    goStraight(2200);  //call goStraight function
    turnRobotRight(650); //call turnRobotRight function
    goStraight(2200);  //call goStraight function
    turnRobotRight(650); //call turnRobotRight function
    goStraight(2200);  //call goStraight function
    turnRobotRight(650); //call turnRobotRight function
    goStraight(2200);  //call goStraight function
    stopRobot();// turn servo off by calling stopRobot function
    
}//end startRobotSquare

//function to start robot routine
void startRobotTriangle(){
    
    goStraight(1000);  //call goStraight function
    turnRobotRight(950); //call turnRobotRight function
    goStraight(1000);  //call goStraight function
    turnRobotRight(950); //call turnRobotRight function
    goStraight(1000);  //call goStraight function
    turnRobotRight(950); //call turnRobotRight function
    goStraight(1000);  //call goStraight function
    stopRobot();// turn servo off by calling stopRobot function
    
}//end startRobotTriangle

//function to test robot routines without affecting other functions/routines
void test(){

  
    
}//end test

