#include <LiquidCrystal.h>

//macros
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//global variables
int mode = 0;
const int modePin = 13;
float id_timer= millis();
const int debounceDelay = 50;
const int mode1_interval = 500;
const int buzzerPin = 3;
float start = 0;
float *start_ptr = &start;


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

void blinkLCD(int pin, String AL, int COL, int ROW, bool sound, int NOTE) {
    
    if (debounce(pin) == HIGH) {
        charLCD(AL, COL, ROW);

        if (sound) {
            tone(buzzerPin, NOTE, 450);
        }
    }

    else {
        charLCD(" ", COL, ROW);
    }
}


void mode1_lower(bool sound) {

    blinkLCD(12, "1", 9, 1, sound, NOTE_C4);
    blinkLCD(11, "2", 10, 1, sound, NOTE_D4);
    blinkLCD(10, "3", 11, 1, sound, NOTE_E4);
    blinkLCD(2, "4", 12, 1, sound, NOTE_F4);
    blinkLCD(16, "5", 13, 1, sound, NOTE_G4);
    blinkLCD(15, "6", 14, 1, sound, NOTE_A4);
    blinkLCD(14, "7", 15, 1, sound, NOTE_B4);

}

void colon(float current) {
    float curr = current;
    if (curr - 1000*(floor(curr/1000) ) < 501) { 
        charLCD(":", 2, 1); }
    else { charLCD(" ", 2, 1); }
}

void stw(float start) {
    float current;
    int min;
    int sec;
    String str_min;
    String str_sec;

    current = millis();

    if (current - start > 120000.00) { 
        *start_ptr = millis();
    }
/*   
    if (start-millis() > current) { //what does this do again???
        start = current;
    }
    */
    
    min = (current - start)/60000;
    sec = (current - start)/1000 - (min*60);

    if (sec*1000 - current)


    if (min>9) { str_min = String(min); }

    else { str_min = "0" + String(min); }

    if (sec>9) { str_sec = String(sec); }
    
    else { str_sec = "0" + String(sec); }

    charLCD(str_min, 0, 1);
    colon(current);
    charLCD(str_sec, 3, 1);
  	Serial.print("Current: ");
  	Serial.println(current);
  	Serial.print("start: ");
    Serial.println(start);

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
    Serial.begin(9600);

  int inputPin[] = {0,1,2,3,10,11,12,13, 14, 15, 16};
    for (int i=0; i<8; ++i) {
        pinMode(inputPin[i], INPUT);
    }

    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    
    lcd.begin(16, 2);           // start the library
    
}

void loop()
{
    //loop varible
    bool sound;

    if (debounce(modePin) == HIGH) {
        mode += 1;
        if (mode > 3) {
            mode = 0;
        }
        lcd.clear();
      	start = millis();
    }

    if (mode == 0) {
        
        charLCD("0", 0, 0);
        stu_id();
        sound = false;
        mode1_lower(sound);
    }

    if (mode == 1) {
        charLCD("1", 0, 0);
        sound = true;
        mode1_lower(sound);
    }

    if (mode == 2) {
        charLCD("2", 0, 0);
      	stw(start);
    }

    if (mode == 3) {
        charLCD("3", 0, 0);
    }

}