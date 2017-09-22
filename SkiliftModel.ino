/***************************************************************************** * 
 *  
 * Tech 4440-01 FA16  12/18/16 
 * Stephanie Eordanidis
 * This program contains routines and functions to control and automate a Ski-lift 
 * Model. The model is approx. 6 feet long by 1 foot wide. 
 * Adjustment of measurement necessary for indivual replication unless utilizing sensors
 * There are three buttons stations. 
 * When button is pressed, a designated ski cart will stop in designated lift locations
 * One servo motor rotates ski lift with rope and pully system.
 *  
****************************************************************************** */ 
#include <Servo.h>  
Servo myservo;  // create servo object to control ski-lift rotation  
/***************************************************************************** * 
*This sections initializes the buttons and their states and lights for the ski-lift model 
****************************************************************************** */ 
// set pin numbers: 
const int buttonPin1 = 11;     // the number of the pushbutton 1 pin 
const int buttonPin2 = 8;     // the number of the pushbutton 2 pin 
const int buttonPin3 = 5;     // the number of the pushbutton 3 pin 
const int bp1G =  12;      // the number of the LED pin 
const int bp1R =  10;      // the number of the LED pin 
const int bp2G =  9;      // the number of the LED pin 
const int bp2R =  7;      // the number of the LED pin 
const int bp3G =  6;      // the number of the LED pin 
const int bp3R =  4;      // the number of the LED pin  
// variables will change: 
int buttonState1 = LOW;         // variable for reading the pushbutton status 
int buttonState2 = LOW;         // variable for reading the pushbutton status 
int buttonState3 = LOW;         // variable for reading the pushbutton status 
int buttonState12 = LOW;         // second variable for reading the pushbutton status 
int buttonState22 = LOW;         // second variable for reading the pushbutton status 
int buttonState32 = LOW;         // second variable for reading the pushbutton status  
//variable to hold last button pressed (retain last location of cart) 
int lastStop = 1; //initialize as 1 
//variable to hold distance used with delay 
int dist = 0; //initialize as 0 
//variable to hold the OK/GREEN light 
int okToGo = 0; //initialize as 0  
/***************************************************************************** * 
*startup code 
****************************************************************************** */ 
void setup() {  
  Serial.begin(9600);  
  myservo.attach(13);  // attaches the servo on pin 13 to the servo object  
  // initialize the LED pin as an output:  
  pinMode(bp1G, OUTPUT); 
  pinMode(bp1R, OUTPUT); 
  pinMode(bp2G, OUTPUT); 
  pinMode(bp2R, OUTPUT); 
  pinMode(bp3G, OUTPUT); 
  pinMode(bp3R, OUTPUT);  
  // initialize the pushbutton pin as an input:  
  pinMode(buttonPin1, INPUT); 
  pinMode(buttonPin2, INPUT); 
  pinMode(buttonPin3, INPUT);  
}   
void loop() {  
/***************************************************************************** * 
* check for button presses and double check their state values 
****************************************************************************** */       
  // read the state of the pushbutton value: 
  buttonState1 = digitalRead(buttonPin1); 
  Serial.println(buttonState1); 
  buttonState2 = digitalRead(buttonPin2); 
  Serial.println(buttonState2); 
  buttonState3 = digitalRead(buttonPin3); 
  Serial.println(buttonState3); 
  delay (1000); 
  // second debounce read the state of the pushbutton value: 
  buttonState12 = digitalRead(buttonPin1); 
  Serial.println(buttonState1); 
  buttonState22 = digitalRead(buttonPin2); 
  Serial.println(buttonState2); 
  buttonState32 = digitalRead(buttonPin3); 
  Serial.println(buttonState3);  
  // check if the pushbutton is pressed.  
  if (buttonState1 == HIGH && buttonState12 == HIGH ) { 
    Serial.println("Button 1"); 
     
    if (lastStop == 1) { 
      //if lastStop == 1, cart is at current stop 
      dist = 0; //dont move cart 
      okToGo = 0; // alert user 
      lastStop = 1; //put last stop as 1 for button 1 
    } else if (lastStop == 2) { 
      //if lastStop == 2, cart is at stop 2 
      dist = 21500; //put the distance for stop 2 to to button 1 
      lastStop = 1; //put last stop as 1 for button 1 
      okToGo = 1; //OK to go 
    } else if (lastStop == 3) { 
      //if lastStop == 3, cart is at stop 3 
      dist = 13500; //put the distance for stop 3 to to button 1 
      lastStop = 1; //put last stop as 1 for button 1 
      okToGo = 1; //OK to go 
    }  
    //check to see if it is ok to proceed 
    if (okToGo == 1) { 
      myservo.write(1400); 
      digitalWrite(bp1G, HIGH); 
      digitalWrite(bp1R, LOW); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(dist);              // wait for 3 second 
      myservo.write(1500); 
    }//end if it is ok to proceed  
    if (okToGo == 0) { 
       
      int counter = 2; 
      while(counter > 0){ 
      tone(2, 1000, 200); //set pizo horn 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, LOW); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(500);              // wait for 1 second 
      tone(2, 1000, 200); //set pizo horn 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(500);              // wait for 1 second 
      counter--; 
      }//end while loop  
    }//end if it is Not Ok to proceed 
  } 
  else if (buttonState2 == HIGH && buttonState22 == HIGH) {  
    Serial.println("Button 2");  
    if (lastStop == 1) { 
      //if lastStop == 1, cart is at stop 1 
      dist = 10000; //put the distance for stop 1 to to button 2 
      lastStop = 2; //put last stop as 2 for button 2 
      okToGo = 1; //OK to go 
    } else if (lastStop == 2) { 
      //if lastStop == 2, cart is current stop 
      dist = 0; //dont move cart 
      okToGo = 0; // alert user 
      lastStop = 2; //put last stop as 2 for button 2 
    } else if (lastStop == 3) { 
      //if lastStop == 3, cart is at stop 3 
      dist = 22800; //put the distance for stop 3 to to button 2 
      lastStop = 2; //put last stop as 2 for button 2 
      okToGo = 1; //OK to go 
    } 
    //check to see if it is ok to proceed 
    if (okToGo == 1) { 
      myservo.write(1400); 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, HIGH); 
      digitalWrite(bp2R, LOW); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(dist);              // wait for 3 second 
      myservo.write(1500); 
    }//end if it is ok to proceed  
    if (okToGo == 0) { 
       
      int counter = 2; 
      while(counter > 0){ 
      tone(2, 1000, 200); //set pizo horn 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, LOW); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(500);              // wait for 1 second 
      tone(2, 1000, 200); //set pizo horn 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(500);              // wait for 1 second 
      counter--; 
      }//end while loop  
    }//end if it is Not Ok to proceed  
  }//end if button2 is high 
   
  else if (buttonState3 == HIGH && buttonState32 == HIGH) {  
    Serial.println("Buttons 3");  
    if (lastStop == 1) { 
      //if lastStop == 1, cart is at stop 1 
      dist = 17200; //put the distance for stop 1 to to button 3 
      lastStop = 3; //put last stop as 3 for button 3 
      okToGo = 1; //OK to go 
    } else if (lastStop == 2) { 
      //if lastStop == 2, cart is at stop 2 
      dist = 7500; //put the distance for stop 2 to to button 3 
      lastStop = 3; //put last stop as 3 for button 3 
      okToGo = 1; //OK to go 
    } else if (lastStop == 3) { 
      //if lastStop == 3, cart is at stop 3 
      dist = 0; //dont move cart 
      lastStop = 3; //put last stop as 3 for button 3 
      okToGo = 0; // alert user 
    }  
    //check to see if it is ok to proceed 
    if (okToGo == 1) { 
      myservo.write(1400); 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, HIGH); 
      digitalWrite(bp3R, LOW); 
      delay(dist);              // wait for 3 second 
      myservo.write(1500); 
    } 
      if (okToGo == 0) { 
         
      int counter = 2; 
      while(counter > 0){ 
      tone(2, 1000, 200); //set pizo horn 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, LOW); 
      delay(500);              // wait for 1 second 
      tone(2, 1000, 200); //set pizo horn 
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(500);              // wait for 1 second 
      counter--; 
      }//end while loop  
      }//end if it is Not Ok to proceed  
    }//end if button3 is high  
    else { 
      Serial.println("Buttons off");  
      digitalWrite(bp1G, LOW); 
      digitalWrite(bp1R, HIGH); 
      digitalWrite(bp2G, LOW); 
      digitalWrite(bp2R, HIGH); 
      digitalWrite(bp3G, LOW); 
      digitalWrite(bp3R, HIGH); 
      delay(3000);              // wait for 3 second 
       
    }//end if no button state is high  
  }//end loop 
