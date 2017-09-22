/******************************************************************************
 * 
 * Tech 4440-01 FA16  10/21/16
 * Stephanie Eordanidis
 * This program contains a switch statement to simulate a traffice light
 * Circumstances for simulation include two road sides with opposing traffic
 * There is a Left turn signal for one road side
 * Button Press simulates car waiting at turn light
 * 
*******************************************************************************/

// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int SSG =  13;      // the number of the LED pin StraightSignal
const int SSR =  12;      // the number of the LED pin StraightSignal
const int OSG =  10;      // the number of the LED pin OpposingSignal
const int OSR =  9;      // the number of the LED pin OpposingSignal
const int LSG =  7;      // the number of the LED pin LeftLightSignal
const int LSR =  6;      // the number of the LED pin LeftLightSignal

// variables will change:
int buttonState = LOW;         // variable for reading the pushbutton status

void setup() {

Serial.begin(9600);

 // initialize the LED pin as an output:

 pinMode(SSG, OUTPUT);
 pinMode(SSR, OUTPUT);
 pinMode(OSG, OUTPUT);
 pinMode(OSR, OUTPUT);
 pinMode(LSG, OUTPUT);
 pinMode(LSR, OUTPUT);

 // initialize the pushbutton pin as an input:

 pinMode(buttonPin, INPUT);

}

void loop() {

 // read the state of the pushbutton value:
 buttonState = digitalRead(buttonPin);

 // check if the pushbutton is pressed.

switch(buttonState) {

      case HIGH :
        digitalWrite(LSG, HIGH);
        digitalWrite(LSR, LOW);
        digitalWrite(SSG, LOW);
        digitalWrite(SSR, HIGH);
        digitalWrite(OSG, LOW);
        digitalWrite(OSR, HIGH);

        delay(3000);              // wait for a second
        break;

      case LOW :
        digitalWrite(LSG, LOW);
        digitalWrite(LSR, HIGH);
        digitalWrite(SSG, HIGH);
        digitalWrite(SSR, LOW);
        digitalWrite(OSG, LOW);
        digitalWrite(OSR, HIGH);

        delay(3000);              // wait for a second

        digitalWrite(LSG, LOW);
        digitalWrite(LSR, HIGH);
        digitalWrite(SSG, LOW);
        digitalWrite(SSR, HIGH);
        digitalWrite(OSG, HIGH);
        digitalWrite(OSR, LOW);

        delay(3000);              // wait for a second

        break;

       default :
         Serial.print("Error in Button State");
         break;

   }
}
