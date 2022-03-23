// C program that displays ambient light intensity value, sounds buzzer, and displays color on LED with option to 
adjust brightness (MSP432 microcontroller)


  #include <Wire.h>
#include "OPT3001.h"
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 
#define USING_MSP430F5529_LAUNCHPAD

Adafruit_TMP006 tmp006;
void printFloat(float value, int places);

const int ACC_X = 23; // accelerometers
const int ACC_Y = 24;
const int BUZZ = 40; // buzzer
const int joystickX = 2; // joysticks
const int joystickY = 26;
const int ledRed = 39, ledBlue = 37, ledGreen = 38; 
char num;
int joystickXState, joystickYState;
String choice, choice2;
String text; // user input 
int totalWords = 0; // stroes the total amount of words in the user's input
String space = ''; // no. of spaces in user's input

opt3001 opt3001;

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  
  opt3001.begin();
  unsigned int readings = 0;

  pinMode(BUZZ,OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledBlue,OUTPUT);
  pinMode(ledGreen,OUTPUT);
 
 
  // get manufacturer ID from OPT3001. Default = 0101010001001001
  readings = opt3001.readManufacturerId();  
  Serial.print("Manufacturer ID: "); 
  Serial.println(readings, BIN);

  // get device ID from OPT3001. Default = 0011000000000001
  readings = opt3001.readDeviceId();  
  Serial.print("Device ID: "); 
  Serial.println(readings, BIN);
  
  // read config register from OPT3001. Default = 1100110000010000
  readings = opt3001.readConfigReg();  
  Serial.print("Configuration Register: "); 
  Serial.println(readings, BIN);

  // read Low Limit register from OPT3001. Default = 0000000000000000
  readings = opt3001.readLowLimitReg();  
  Serial.print("Low Limit Register: "); 
  Serial.println(readings, BIN);
  
  // read High Limit register from OPT3001. Default = 1011111111111111
  readings = opt3001.readHighLimitReg();  
  Serial.print("High Limit Register: "); 
  Serial.println(readings, BIN);  

  if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("The sensor is not found");
    while(1);
}
  
}

void loop() {
  // troubleshoot menu option
  void menu() {
    Serial.print("1. Read the object temperature and print the value in Celsius");
    Serial.print("2. Read the accelerometer and print the x and y angle");
    Serial.print("3. Read the ambient light intensity and print the Lux value");
    Serial.print("4. Read the joystick x and y and print the x and y angle");
    Serial.print("5. Write the input text to the LCD screen by capitalizing the first alphabet of the input text along with the number of spaces, alphabets, words, and vowels");
    Serial.print("6. Generate a color on the LED [indigo or tan] with a brightness [0 to 100%]");
    Serial.print("7. Generate a beep tone on the buzzer");

    Serial.print("Please input the selection [1-7]: ");
    Serial.println(num);
  }
      // displays object temperature
      void temp() {
      float objt = tmp006.readObjTempC();
      Serial.print("Object Temperature: "); Serial.print(objt,2); Serial.println("*C");
    }
      // displays the accelerometer values for x and y axis 
      void accel() {
      int xValue = (((int) analogRead(ACC_X)) - 2048);
      int yValue = (((int) analogRead(ACC_Y)) - 2048);
      Serial.println(xValue,2);
      Serial.println(yValue,2);
      // checks for appropriate angle ranges
      if (xValue > 90 || xValue < -90) {
        Serial.print("Invalid x angle");
      }
      if (yValue > 90 || yValue < -90) {
        Serial.print("Invalid y angle");
      }
      }
      // displays ambient light intensity
      void ambLight() {
      // Variables
      uint32_t readings;
      readings = opt3001.readResult();  
  
      Serial.print("LUX Readings = ");
      Serial.println(readings, DEC);
    }
      // displays joystick values for x and y axis
      void joystick() {
        // read the analog value of joystick x axis
        joystickXState = analogRead(joystickX);
        Serial.print("Joystick X = ");
        Serial.print(joystickXState,2);

        // read the analog value of joystick y axis
        joystickYState = analogRead(joystickY);
        Serial.print("Joystick Y = ");
        Serial.print(joystickYState,2);
        // checks for appropriate angle ranges
        if (xValue > 20 || xValue < -20) {
        Serial.print("Invalid x angle");
      }
      if (yValue > 20 || yValue < -20) {
        Serial.print("Invalid y angle");
      }
      }
      // generate beep if user selects the menu option
      void beep() {
        tone(BUZZ,4000,2000);
        Serial.print("Tone generated!")
      }
      // generate color on the LED and adjust based on brightness
      void color() {
      Serial.print("Input the color: ");
      Serial.println(choice);
      if (choice == "tan") {
        RGB(255,192,128);
      }
      if (choice == "indigo") {
        RGB(75,0,130);
      }
      Serial.print("Input the brightness: ");
      Serial.println(choice2);
      if (choice2 == "10%") && (choice == "tan") {
        RGB(26,19,13);
      }
      if (choice2 == "20%") && (choice == "tan") {
        RGB(51,38,26);
      }
      if (choice2 == "30%") && (choice == "tan") {
        RGB(77,58,38);
      }
      if (choice2 == "40%") && (choice == "tan") {
        RGB(102,77,51);
      }
      if (choice2 == "50%") && (choice == "tan") {
        RGB(128,96,64);
      }
      if (choice2 == "60%") && (choice == "tan") {
        RGB(153,115,77);
      }
      if (choice2 == "70%") && (choice == "tan") {
        RGB(179,134,90);
      }
      if (choice2 == "80%") && (choice == "tan") {
        RGB(204,154,102);
      }
      if (choice2 == "90%") && (choice == "tan") {
        RGB(230,173,115);
      }
      else if (choice2 == "10%") && (choice == "indigo") {
        RGB(8,0,13);
      }
      else if (choice2 == "20%") && (choice == "indigo") {
        RGB(15,0,26);
      }
      else if (choice2 == "30%") && (choice == "indigo") {
        RGB(23,0,39);
      }
      else if (choice2 == "40%") && (choice == "indigo") {
        RGB(30,0,52);
      }
      else if (choice2 == "50%") && (choice == "indigo") {
        RGB(38,0,65);
      }
      else if (choice2 == "60%") && (choice == "indigo") {
        RGB(45,0,78);
      }
      else if (choice2 == "70%") && (choice == "indigo") {
        RGB(53,0,91);
      }
      else if (choice2 == "80%") && (choice == "indigo") {
        RGB(60,0,104);
      }
      else if (choice2 == "90%") && (choice == "indigo") {
        RGB(68,0,117);
      }
      }
      
      // print number of vowels, spaces, words. Also, the first letter in the user's text is capitalized
      void screen() {
        for(int i = 0; i < text.length(); i++) {
          Serial.print("Input the text: ");
          if (isUpperCase(text[0])) {
              Serial.println(text[0]);
          }
          Serial.print("Number of spaces: ");
          if (isSpace(text)) {
             Serial.println(text);
          }
          Serial.print("Number of alphabets: ");
          if (isAlpha(text)) {
            Serial.println(text);
          }
          Serial.print("Number of vowels: ");
          if (text == 'a' || text == 'i' || text == 'u' || text == 'o' || text == 'e') {
            Serial.println(text);
          }
          else {
            Serial.print("No vowels were found");
          }
          Serial.print("Number of words: ");
          if (text[i] == '' || text[i] == '\n' || text[i] == '\t') {
            totalWords++;
          }
          Serial.println(text, totalWords);
        }
        }
     
   unsigned long currTime = millis(); // stores the current tiem
   int sTime = 0;  
    if (Serial.available() > 0) {
        num = Serial.read(); // reads serial data value via the number menu number selected by the user

        if (num == '1') {
          temp();
        }
        if ((currTime-sTime) == 5000) { // if 5 seconds have passed after the request was completed, the menu is shown once more
          menu();
        }
        if (num == '2') {
          accel();
        }
        if ((currTime-sTime) == 5000) {
          menu();
        }
        if (num == '3') {
          ambLight();
        }
        if ((currTime-sTime) == 5000) {
          menu();
        }
        if (num == '4') {
          joystick();
        }
        if ((currTime-sTime) == 5000) {
          menu();
        }
        if (num == '7') {
          beep();
        }
        if ((currTime-sTime) == 5000) {
          menu();
        }
        if (num == '6') {
          color();
        }
        if ((currTime-sTime) == 5000) {
          menu();
        }
        if (num == '5') {
          screen();
        }
        if ((currTime-sTime) == 5000) {
          menu();
        }
        
        }
 // declares the RGB values for the color function      
 void RGB(int redVal, int greenVal, int blueVal) {
    analogWrite(ledRed, redVal);
    analogWrite(ledGreen, greenVal);
    analogWrite(ledBlue, blueVal);
}

}
  
  
