#include <Time.h>
#include <TimeLib.h>

//Sample using LiquidCrystal library
#include <LiquidCrystal.h>


/*******************************************************
This program is used with a DFRobot LCD keypad shield. It implements a simple UI for setting values to
the variable freq and duty through the buttons of the shield.

Code written by Maxime Boudreau (February 2017) using the example code from Mark Bramwell (July 2010)

********************************************************/

//Initial values for the ajustable variables.
double freq = 1; //1 Hz
double duty = 50;// 50%

int lcd_key     = 0;
int adc_key_in  = 0;

int modeLev1 = 0; //Time mode 
int secondOfLastUpdate = 0;


// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons



int buttonDelay = 120; //Speed at wich the Arduino respond to user entry.

double incValF = 1;
double incValD = 1;

int displayMode = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define mFreq     0
#define mDuty     1

int Lev1Val = 2;

#define Msg1[0] = "Return";
#define Msg1[1] = "Parameters"; 
#define Msg1[2] = "Time"; 
#define Msg1[3] = "Led Mode"; 

#define Msg2[1][0] = "Return";
#define Msg2[1][1] = "Set time";
#define Msg2[1][2] = "Set date";

#define Msg2[2][0] = "Return";
#define Msg2[2][1] = "Set time";




void setup()
{
  // Set the time
  setTime(0, 0, 0, 0, 0, 0);

  lcd.begin(16, 2);              // start the library

  //Intro display of the LCD
  lcd.setCursor(0, 0);
  lcd.print("Strob. by MxBoud");
  delay(1000);

  Serial.begin(9600);
  updateLCD(1);

}

void loop()
{
  lcd_key = readLCDcontroller();  // read the buttons
  respondToButtonInput(); //Do what the button is supposed to do

  
}



int readLCDcontroller() //Tells wich button is selected
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}

void respondToButtonInput() //Respond to current lcd_key and initiate corresponding callback.
{

  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
      {
        
        updateLCD(1);
        delay(buttonDelay * 2);
        break;
      }
    case btnLEFT:
      {
       
        updateLCD(1);
        delay(buttonDelay * 2);
        break;
      }
    case btnUP:
      {
       
        updateLCD(1);
        delay(buttonDelay);
        break;
      }
    case btnDOWN:
      {
        
        updateLCD(1);
        delay(buttonDelay);
        break;
      }
    case btnSELECT: // Switch between frequency mode and dutycycle mode
      {
        if (displayMode == mFreq) {
          displayMode = mDuty;
        }
        else if (displayMode == mDuty) {
          displayMode = mFreq;
        }
        updateLCD(1);
        delay(4 * buttonDelay);
        time_t t = now(); // Store the current time in time
        Serial.println(hour(t));
        Serial.println(minute(t));
        Serial.println(second(t));

        break;
      }
    case btnNONE:
      {
        
       // updateLCD();

       //Nothing is going on. If LCD shows the time, must update it every seconds. 
       if (modeLev1 ==0){
        
        time_t t = now(); 
        int currentSecond = second(t);
        if (currentSecond != secondOfLastUpdate){
          updateLCD(0);
          secondOfLastUpdate = currentSecond;
        }
        
       }
        break;
      }
  }

}



String formatTime( time_t t) //To make a string LCD friendly from the time
{
  int H = hour(t);
  int M = minute(t);
  int S = second(t);
  String sH;
  String sM;
  String sS;

  if (H<10) {
    sH = "0"+String(H);  
  }
  else {
    sH = String(H);
  }
  if (M<10) {
    sM = "0"+String(M);  
  }
  else {
    sM = String(M);
  }
  if (S<10) {
    sS = "0"+String(S);  
  }
  else {
    sS = String(S);
  }

  return sH + ":" + sM + ":" + sS; 
}
void updateLCD(int doClear)
{
  if (doClear ==1 ) {
  lcd.clear();
  }
  // level1
  switch (1) {
    case 1:  {
        //Display mode
        time_t t = now();
        String timeString = formatTime(t);
        lcd.setCursor(0, 0); //First row
        lcd.print("Time");
        lcd.setCursor(0, 1);
        lcd.print(timeString);

        break;
      }
    case 2:
      break;
    case 3:
      break;
  }
}







