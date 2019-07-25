#include <Keypad.h>
#include <Keypad_MC17.h>    // I2C i/o library for Keypad
#include <Wire.h>           // I2C library for Keypad_MC17

#define I2CADDR 0x20        // address of MCP23017 chip on I2C bus

const byte ROWS = 4; //four rows
const byte COLS = 8; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'a', 'b', 'c', 'd', 'e'},
  {'4', '5', '6', 'f', 'g', 'h', 'i', 'j'},
  {'7', '8', '9', 'k', 'l', 'm', 'n', 'o'},
  {'*', '0', '#', 'p', 'q', 'r', 's', 't'}
};
byte rowPins[ROWS] = {8, 9, 10, 11}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {0, 1, 2, 3, 4, 5, 6, 7}; //connect to the column pinouts of the kpd

// modify constructor for I2C i/o
Keypad_MC17 kpd = Keypad_MC17( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );



void setup() {
  Serial.begin(9600);
  kpd.begin( );            // also starts wire library
  kpd.setDebounceTime(1);
}

unsigned long loopCount = 0;
unsigned long startTime = micros();
unsigned long lastDeltaTime;
unsigned long deltaTime;
unsigned long deltaDeltaTime;
String msg = "";
float avgDDT;

unsigned long delDelTimes [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
int dDTIndex;

boolean checkNow;
boolean frameAfter;

void loop() {

  loopCount++;

  lastDeltaTime = deltaTime;
  deltaTime = micros() - startTime;
  startTime = micros();

  if (deltaTime > lastDeltaTime)
    deltaDeltaTime = deltaTime - lastDeltaTime;
  else
    deltaDeltaTime = lastDeltaTime - deltaTime;

  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (frameAfter)
  {
    Serial.print("FrameAfter ");
    Serial.println(deltaDeltaTime);
    frameAfter = false;
  }

  if (checkNow)
  {
    checkNow = false;
    frameAfter = true;
  }

  if (kpd.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:
            msg = " PRESSED.";
            checkNow = true;
            break;
          case HOLD:
            msg = " HOLD.";
            checkNow = true;
            break;
          case RELEASED:
            msg = " RELEASED.";
            checkNow = true;
            break;
          case IDLE:
            msg = " IDLE.";
        }


        Serial.print("Key ");
        Serial.println(kpd.key[i].kchar);
        Serial.println(msg);
      }
    }
  }
}  // End loop
