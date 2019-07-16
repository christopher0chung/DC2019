//-----------------------------------------------------------------------------------------------------------
//   SCREEN
//-----------------------------------------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 screen = Adafruit_AlphaNum4();

void screenInit() {
  screen.begin(0x70);
  screen.setBrightness(0);
  screen.writeDisplay();
}

void screenPrint(int value) {
  char buff[4];
  String screenVal = String(value);
  screenVal.toCharArray(buff, 4);

  for (int i = 0; i < 4; i++) {
    screen.writeDigitAscii(i, ' ');
  }

  if (screenVal.length() == 1) {
    screen.writeDigitAscii(3, buff[0]);
  }

  if (screenVal.length() == 2) {
    screen.writeDigitAscii(2, buff[0]);
    screen.writeDigitAscii(3, buff[1]);
  }

  if (screenVal.length() == 3) {
    screen.writeDigitAscii(1, buff[0]);
    screen.writeDigitAscii(2, buff[1]);
    screen.writeDigitAscii(3, buff[2]);
  }

  if (screenVal.length() == 4) {
    screen.writeDigitAscii(0, buff[0]);
    screen.writeDigitAscii(1, buff[1]);
    screen.writeDigitAscii(2, buff[2]);
    screen.writeDigitAscii(3, buff[3]);
  }
}

//-----------------------------------------------------------------------------------------------------------
//   BUTTONS
//-----------------------------------------------------------------------------------------------------------
#include <CD4021.h>

byte dataPin = 9;
byte latchPin = 8;
byte clockPin = 7;

ShiftReg buttons = ShiftReg(dataPin, latchPin, clockPin);

void testButtons() {
  for (int loc = 0; loc < 304; loc++) {
    if (buttons.vals[loc] != buttons.lastVals[loc]) {
      if (buttons.vals[loc] == 1) {
        Serial.print("Key");
        Serial.print("\t");
        Serial.print("loc:");
        Serial.print(loc);
        Serial.println();
      }
      buttons.lastVals[loc] = buttons.vals[loc];
    }
  }
}

//-----------------------------------------------------------------------------------------------------------
//   POTENTIOMETERS
//-----------------------------------------------------------------------------------------------------------
#include <CD4067.h>

byte selPins[3] = {15, 16, 17};
byte readPins[3] = {A3, A4, A5 };
MuxIn pots = MuxIn(selPins[0], selPins[1], selPins[2], A6, A7);

void potsInit() {
  for (int i = 0; i < 3; i++) pots.attach(readPins[i]);
  pots.smoothAmount = .9;
}

void testPots() {
  for (int loc = 0; loc < 26; loc++) {
    if (pots.vals[loc] != pots.lastVals[loc]) {
      Serial.print("Pot");
      Serial.print("\t");
      Serial.print("loc:");
      Serial.print(loc);
      Serial.print("\t");
      Serial.println(pots.vals[loc]);
      pots.lastVals[loc] = pots.vals[loc];
      screenPrint(pots.vals[loc]);
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
  for (byte i = 0; i < 6; i++) {
    leds.setPosition(i, panelArrange[i], 0);
    leds.setRotation(i, 3);
  }
}
