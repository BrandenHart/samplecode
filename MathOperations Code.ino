/* 1. When the command POWm n R is typed on the serial communication console, the red LED 
(J4.39) should blink based on the computation of m^n (m to the power n). (Example values of m 
and n: if m = 2 and n = 1 then 2 blinks, if m = 2 and n = 2 then 4 blinks, if m = 3 and n = 2 then 9 
blinks, and so on). Do not use the in-built pow () function for the computation of m^n.
2. When the command SRS n G is typed on the serial communication console, the green LED 
(J4.38) should blink based on the series an = 3an-1 - an-2 where a1 = 1 and a2 = 1. (Example 
values of n: if n = 1 then 1 blink as a1 = 1, if n = 2 then 1 blink as a2 = 1, if n = 3 then 2 blinks as 
a3 = 2, and so on) 
*/


#include <Wire.h>
#include <string.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 

Adafruit_TMP006 tmp006;
void printFloat(float value, int places);

#define ledRed RED_LED // red LED
#define ledGreen GREEN_LED // green LED
const int buttonOne = 33; // Push button pin J4.33
const int buttonTwo = 32; // Push button pin J4.32
const int xpin = 23;      // x-axis of the accelerometer
const int ypin = 24;     // y-axis
const int zpin = 25;     // z-axis (only on 3-axis models)
int a1 = 0;
int a2 = 0;
int z = 0;
int nextTerm = 0;

int buttonOneState = 0; // detects if the button is pushed
int buttonTwoState = 0; // detects if the button is pushed
String command; // holds the command 
boolean stringCorrect = false; // checks if the command entered is acceptable
int m = 0; // power function variable (base)
int n = 0; // power function variable (exponent)

void setup() {
pinMode(ledRed,OUTPUT);
pinMode(ledGreen,OUTPUT);
pinMode(buttonOne,INPUT_PULLUP);
pinMode(buttonTwo,INPUT_PULLUP); 

Serial.begin(9600);
analogReadResolution(12);
input.reserve(200); // delegated to the string command

// 
if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("The sensor is not found");
    while(1);
}

}

void loop() {
  // if button 1 is pressed, display the temperature
  buttonOneState = digitalRead(buttonOne);
  if(buttonOneState == LOW) {
    float objt = tmp006.readObjTempC();
    Serial.print("Object Temperature: "); Serial.print(objt); Serial.println("*C");
    Serial.println("\nExecuted");
    delay(1000);
    }

    // if button 2 is pressed, display the accelemerometer values
    buttonTwoState = digitalRead(buttonTwo);
    if(buttonTwoState == LOW) {
     Serial.print(((int) analogRead(xpin)) - 2048);
     // print a tab between values:
     Serial.print("\t");
     Serial.print(((int) analogRead(ypin)) - 2048);
     // print a tab between values:
     Serial.print("\t");
     Serial.print(((int) analogRead(zpin)) - 2048);
     Serial.println(); 
     Serial.println("\nExecuted")
     delay(1000);
     }

     if(Serial.available() > 0) {
      if(stringCorrect == false)
      {
        char commandChar = (char)Serial.read();
        if(commandChar == '\n')
        {
          stringCorrect = true;
        }
        else {
          command +=commandChar;
        }
      }
     }
        if(stringCorrect == true) {
          Serial.println(command);
          if(command == "POW m n R") {
            int result = 1;
            for(int i = 0; i < n; ++i) {
              result*=m;
              digitalRead(result);
              digitalWrite(ledRed, HIGH);
              Serial.println("\nExecuted");
              }
          }
            
          }
          else if(command == "SRS n G") {
           for(int i = 1; i <= z; ++i) {
             sum = 3*a1[i] - a2[i];
             nextTerm = sum;
             digitalRead(nextTerm);
             digitalWrite(ledGreen, HIGH);
             Serial.println("\nExecuted");
           }
          }

          else {
          Serial.println("Invalid Command");
        }
        stringCorrect = false;
        command = "";
        }
   
      
     
      
      
      
      

     
  
  
  
