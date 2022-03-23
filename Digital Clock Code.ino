#include <Wire.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 

Adafruit_TMP006 tmp006;
void printFloat(float value, int places);


// put your setup code here, to run once:
const int ledPin = RED_LED; // red LED
const int buttonOne = 33; // Push button pin J4.33
const int buttonTwo = 32; // Push button pin J4.32
const int buzzerPin = 40; // Buzzer pin J4.40
const int xpin = 23;      // x-axis of the accelerometer
const int ypin = 24;     // y-axis
const int zpin = 25; // z-axis (only on 3-axis models)

long idleTime = 0; // idle time of board
int analogValue; // check y-axis
int h = 0; // hours
int m = 0; // minutes
int s = 0; // seconds
// S1 interrupt
      void pressOne() {
        if (buttonOne == HIGH) {
          buttonTwo = LOW;
        }
      }
        // S2 interrupt
        void pressTwo() {
        if (buttonTwo == HIGH) {
          buttonOne = LOW;
        }
        }  

void setup() {
pinMode(ledPin,OUTPUT);
pinMode(buzzerPin,OUTPUT);
pinMode(buttonOne,INPUT_PULLUP);
pinMode(buttonTwo,INPUT_PULLUP); 
attachInterrupt(buttonOne,pressOne,RISING);
attachInterrupt(buttonTwo,pressTwo,RISING);


Serial.begin(9600);
analogReadResolution(12);

if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("The sensor is not found");
    while(1);
}


}

void loop() {
  // print the sensor values:
  Serial.print(((int) analogRead(xpin)) - 2048);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(((int) analogRead(ypin)) - 2048);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(((int) analogRead(zpin)) - 2048);
  Serial.println();
  // delay before next reading:
  delay(100);

  // increment hour if S1 is pressed (0-23)
  if (buttonOne == HIGH) {
    for(i=0; i < 23; i++) {
      h = h + 1;
      h++;
    }
    
    else {
    if (h++ >= 23) { 
      h = "00";
      h++;
    }
    }
    else {
      buttonOne = LOW;
    }
  }
    // increment minutes if S2 is pressed (0-59)
    if (buttonTwo == HIGH) {
      for(i = 0; i < 59; i++) {
        m = m+1;
        m++;
      }
      else if (m++ >= 59) {
        m = "00";
        m++;
      }
      else {
        buttonTwo = LOW;
      }
    }
      // beep when hour or minute is changed by S1 OR S2
      void beep() {
        if ((buttonOne = HIGH) && (buttonTwo ==LOW)) {
          tone(buzzerPin, 4000, 2000);
        }
        else {
          if ((buttonOne = LOW) && (buttonTwo == HIGH)) {
            tone(buzzerPin, 4000, 2000);
          }
        }
      }
      // blink red LED on and off
      void blink () {
        sTime = millis();
        if (sTime >= 500) {
          ledPin = HIGH;
          else {
            ledPin = LOW;
          }
        }
          if (sTime >= 1000) {
            s=s+1;
            s++;
          }
          if (s >= 59) {
            m=m+1; 
        }
      }
      // S1 interrupt
      void pressOne() {
        if (buttonOne == HIGH) {
          buttonTwo = LOW;
        }
      }
        // S2 interrupt
        void pressTwo() {
        if (buttonTwo == HIGH) {
          buttonOne = LOW;
        }
        }
       // clear board if idle for 5 seconds
        void clearBoard () {
          lcd.begin();
          Serial.println ("HH: ", "MM:", "SS: ")
          lcd.print(h);
          lcd.print(m);
          lcd.print(s);
          if (((sTime - idleTime) / 1000) == 5) {
            lcd.clear();
            Serial.println("---");
            Serial.println();
          }
          // print clock if board is tilited 30 degrees
          analogValue = analogRead(ypin); // read y-axis 
          if (analogValue == 2078) {
            lcd.print("HH: ", "MM:", "SS: ");
            lcd.print(h);
            lcd.print(m);
            lcd.print(s);
             
           }
        }
    
    
    
  

 
  
  
  
 }
  
  
