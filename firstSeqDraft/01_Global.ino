
//-----------------------------------------------------------------------------------------------------------
//   Buttons
//-----------------------------------------------------------------------------------------------------------
#include <Keypad.h>
#include <Keypad_MC17.h>
#include <Wire.h>

#define I2CADDR 0x20

const byte rows = 8;
const byte cols = 8;
byte rowPins[rows] = {15, 14, 13, 12, 11, 10, 9, 8};
byte colPins[cols] = {0, 1, 2, 3, 4, 5, 6, 7};
char charMap[rows][cols];
bool states[rows][cols];

Keypad_MC17 keys(makeKeymap(charMap), rowPins, colPins, rows, cols, I2CADDR );

void keysInit() {
  keys.begin();
  keys.setDebounceTime(1);
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      charMap[x][y] = 49 + y + (x * rows);
      states[x][y] = 0;
    }
  }
}

void keysUpdate() {

  char key = keys.getKey();
  if (key) {
    Serial.println(key);
  }

  if (keys.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (keys.key[i].stateChanged) {
        byte charX = (keys.key[i].kchar - 49) % 8;
        byte charY = (keys.key[i].kchar - 49) / 8;
        switch (keys.key[i].kstate) {
          case PRESSED:
            Serial.print(keys.key[i].kchar);
            Serial.print("\t");
            Serial.print(1);
            Serial.print("\t");
            Serial.print(charX);
            Serial.print(", ");
            Serial.println(charY);
            states[charX][charY] = 1;
            break;
          case HOLD:
            break;
          case RELEASED:
            Serial.print(keys.key[i].kchar);
            Serial.print("\t");
            Serial.print(0);
            Serial.print("\t");
            Serial.print(charX);
            Serial.print(", ");
            Serial.println(charY);
            states[charX][charY] = 0;
            break;
          case IDLE:
            break;
        }
      }
    }
  }


}


//-----------------------------------------------------------------------------------------------------------
//   LEDS
//-----------------------------------------------------------------------------------------------------------
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

byte csPin = 20;
byte horiDisplays = 6;
byte vertiDisplays = 1;
byte panelArrange[6] = {5, 4, 0, 1, 2, 3};
Max72xxPanel leds = Max72xxPanel(csPin, horiDisplays, vertiDisplays);

void ledsInit() {
  leds.setIntensity(0);
  leds.fillScreen(0);

  // *** Comment out for TestBed
  //  for (byte i = 0; i < 6; i++) {
  //    leds.setPosition(i, panelArrange[i], 0);
  //    leds.setRotation(i, 3);
  //  }
}

void ledsUpdate()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      leds.drawPixel(i, j, states[i][j]);
    }
  }
}

//-----------------------------------------------------------------------------------------------------------
//   POTENTIOMETERS
//-----------------------------------------------------------------------------------------------------------
#include <CD4067.h>

byte selPins[4] = {14, 15, 16, 17};
byte readPins[2] = {A6, A7};
bool smoothEnable = 1;
MuxIn pots = MuxIn(selPins[0], selPins[1], selPins[2], selPins[3], smoothEnable);

void potsInit() {
  for (int i = 0; i < 2; i++) pots.attach(readPins[i]);
  pots.smoothAmount = .9;
}

//-----------------------------------------------------------------------------------------------------------
//   Counter Stuff
//-----------------------------------------------------------------------------------------------------------
#include "CounterLib.h"

int inputNodeXs[6] = {0, 1, 5, 6, 7, 8};
int inputNodeYs[6] = {0, 0, 0, 0, 0, 0};
int outputNodeXs[16] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7};
int outputNodeYs[16] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2};

Counter c1(inputNodeXs, inputNodeYs, outputNodeXs, outputNodeYs);


//-----------------------------------------------------------------------------------------------------------
//   TIMER
//-----------------------------------------------------------------------------------------------------------

unsigned long lastTime;
unsigned long delTime;

unsigned long accum;
unsigned long rollOver;

void timerUpdate()
{
  delTime = micros() - lastTime;
  lastTime = micros();
  //Serial.println(delTime);

  accum += delTime;
  if (accum >= 100000)
  {
    accum -= 100000;
    c1.tick(states);
  }
}
