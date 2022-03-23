/* 1. When the push button S1 (J4.33) of the MKII board is pressed, blink (on and off) the 
red LED (J4.39) based on the series ((n+1)^2) /4) where n is the number of presses. (1st press 
→ 1 blink, 2nd press → 2 blinks, 3rd press → 4 blinks and so on)
2. When the push button S2 (J4.32) of the MKII board is pressed, blink (on and off) the 
green LED (J4.38) based on the number of presses. (1stpress → 1 blink, 2ndpress → 2 
blinks, 3rdpress → 3 blinks, 4thpress → 4 blinks, and so on)
3. Each time when the switch S1 or S2 is pressed, generate a beep using the buzzer
*/

#define NOTE_C4_1 260
#include "pitches.h"

// pin configurations
const int buttonOne = 33;     // the number of the pushbutton pin
const int buttonTwo = 32;     // the number of the pushbutton pin
const int ledGreen =  38;      // the number of the LED pin
const int ledRed =  39; // the number of the LED pin
const int buzzerPin = 40;
const int pushButton = 1; // push button on board (P1.1)

int melody[] = {
   NOTE_C4_1,NOTE_C4, NOTE_D4, NOTE_C4,NOTE_F4,NOTE_E4,
   NOTE_C4_1,NOTE_C4,NOTE_D4,NOTE_C4,NOTE_G4,NOTE_F4,
   NOTE_C4_1,NOTE_C4,NOTE_C5,NOTE_A4,NOTE_F4,NOTE_F4, NOTE_E4,NOTE_D4,
   NOTE_AS4,NOTE_AS4,NOTE_A4,NOTE_F4,NOTE_G4,NOTE_F4};


// variables will change:
int buttonOneState = 0;         // variable for reading the pushbutton #1 status
int buttonTwoState = 0;   // variable for reading the pushbutton #2 status
int numOnePress = 0; // amount of times that S1 is pressed
int numTwoPress = 0; // amount of times that S2 is pressed
int n = 0; // S1 iterator
int x = 0; // S2 iterator


void setup() {
  // put your setup code here, to run once:
  // initialize the LED pins as  output:
  pinMode(ledRed, OUTPUT);     
  pinMode(ledGreen, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);    
   
  // initialize the pushbutton pin as an input:
  pinMode(buttonOne, INPUT);     
  pinMode(buttonTwo, INPUT); 
  pinMode(pushButton, INPUT);    
}



void loop() {
  // put your main code here, to run repeatedly: 
  // read the state of the pushbutton value:

 buttonOneState = digitalRead(buttonOne);
 if (n > 0) {
  numOnePress = ((n+1)*(n+1))/ 4;
 }
 for (int thisNote = 0; thisNote < 26; thisNote++) {
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonOneState == LOW) {   
    // turn LED on:    
    digitalWrite(ledRed, HIGH);
    tone(buzzerPin,melody[thisNote]); 
    delay(numOnePress);  
  } 
  
  else {
    // turn LED off:
    digitalWrite(ledRed, LOW); 
  }


delay(2000);

buttonTwoState = digitalRead(buttonTwo);
if (x > 0) {
  numTwoPress = x;
}

if (buttonTwoState == LOW) {   
    // turn LED on:    
    digitalWrite(ledGreen, HIGH);
    tone(buzzerPin,melody[thisNote]); 
    delay(numTwoPress);  
  }
   else {
    // turn LED off:
    digitalWrite(ledGreen, LOW); 
  
 }
 // push button stops the operation of the other two LEDs
 if (pushButton == HIGH) { 
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
 }
 }
}
