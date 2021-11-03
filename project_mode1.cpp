#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//global variables
int mode = 0;
const int modePin = 13;
float id_timer= millis();
const int debounceDelay = 50;
const int mode1_interval = 500;


//functions

void charLCD(String AL, int COL, int ROW) {
    lcd.setCursor(COL, ROW);
    lcd.print(AL);
}

void clearspcf(int space, int COL, int ROW) {
    String spaces = " ";

    for (int i=1; i<space; ++i) {
        spaces += " ";
    }

    lcd.setCursor(COL, ROW);
    lcd.print(spaces);
}

void stu_id() {

    if (millis()- id_timer > 10*mode1_interval) {
         clearspcf(10, 6, 0);

        if (millis()-id_timer > 11*mode1_interval) {
        id_timer = millis();
        }
    }

    else {
        
        if (millis()-id_timer > 100) {
            charLCD("6", 6, 0);
        }

        if (millis()-id_timer > 1*mode1_interval) {
            charLCD("2", 7, 0);
        }

        if (millis()-id_timer > 2*mode1_interval) {
            charLCD("1", 8, 0);
        }

        if (millis()-id_timer > 3*mode1_interval) {
            charLCD("0", 9, 0);
        }

        if (millis()-id_timer > 4*mode1_interval) {
            charLCD("5", 10, 0);
        }

        if (millis()-id_timer > 5*mode1_interval) {
            charLCD("0", 11, 0);
        }

        if (millis()-id_timer > 6*mode1_interval) {
            charLCD("5", 12, 0);
        }

        if (millis()-id_timer > 7*mode1_interval) {
            charLCD("4", 13, 0);
        }

        if (millis()-id_timer > 8*mode1_interval) {
            charLCD("3", 14, 0);
        }

        if (millis()-id_timer > 9*mode1_interval) {
            charLCD("1", 15, 0);
        }
    }
}

void blinkLCD(int pin, String AL, int COL, int ROW) {
    
    if (debounce(pin) == HIGH) {
        charLCD(AL, COL, ROW);
    }

    else {
        charLCD(" ", COL, ROW);
    }
}


void mode1_lower() {

    blinkLCD(12, "1", 9, 1);
    blinkLCD(11, "2", 10, 1);
    blinkLCD(10, "3", 11, 1);
    blinkLCD(2, "4", 12, 1);
    blinkLCD(1, "5", 13, 1);
    blinkLCD(15, "6", 14, 1);
    blinkLCD(14, "7", 15, 1);

}


bool debounce(int pin)
{
  bool state;
  bool previousState;

  previousState = digitalRead(pin);          
  for(int counter=0; counter < debounceDelay; counter++)
  {
      delay(1);                  
      state = digitalRead(pin);  
      if( state != previousState)
      {
         counter = 0; 
         previousState = state;  
      }
  }
  return state;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{

  int inputPin[] = {0,1,2,3,10,11,12,13, 14, 15};
    for (int i=0; i<8; ++i) {
        pinMode(inputPin[i], INPUT);
    }

    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    
    lcd.begin(16, 2);           // start the library
    
}

void loop()
{
    if (debounce(modePin) == HIGH) {
        mode += 1;
        if (mode > 3) {
            mode = 0;
        }
    }

    if (mode == 0) {
        charLCD("0", 0, 0);
        stu_id();
        mode1_lower();
    }

    if (mode == 1) {
        charLCD("1", 0, 0);
    }

    if (mode == 2) {
        charLCD("2", 0, 0);
    }

    if (mode == 3) {
        charLCD("3", 0, 0);
    }
    //lcd.setCursor(9, 1);       // move cursor to second line "1" and 9 spaces over
    //lcd.print(millis()/1000);  // display seconds elapsed since power-up
}