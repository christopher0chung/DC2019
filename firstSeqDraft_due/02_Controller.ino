//---------------------------------------------------------------
//   SCREEN
//---------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 screen = Adafruit_AlphaNum4();

void screenInit() {
  screen.begin(0x70);
  screen.setBrightness(0);
  screenClear();
  screen.writeDisplay();
}

void  screenClear() {
  for (int i = 0; i < 4; i++) {
    screen.writeDigitAscii(0, ' ');
  }
}

void screenPrint(int val) {
  String text = String(val);
  screenPrint(text);
}

void screenPrint(String text) {  // buff[4] doesn't work and i have no clue why
  char buff[5];
  text.toCharArray(buff, 5);
  if (text.length() == 1) {
    screen.writeDigitAscii(0, ' ');
    screen.writeDigitAscii(1, ' ');
    screen.writeDigitAscii(2, ' ');
    screen.writeDigitAscii(3, buff[0]);
  }
  if (text.length() == 2) {
    screen.writeDigitAscii(0, ' ');
    screen.writeDigitAscii(1, ' ');
    screen.writeDigitAscii(2, buff[0]);
    screen.writeDigitAscii(3, buff[1]);
  }
  if (text.length() == 3) {
    screen.writeDigitAscii(0, ' ');
    screen.writeDigitAscii(1, buff[0]);
    screen.writeDigitAscii(2, buff[1]);
    screen.writeDigitAscii(3, buff[2]);
  }
  if (text.length() == 4) {
    screen.writeDigitAscii(0, buff[0]);
    screen.writeDigitAscii(1, buff[1]);
    screen.writeDigitAscii(2, buff[2]);
    screen.writeDigitAscii(3, buff[3]);
  }
  screen.writeDisplay();
}

//---------------------------------------------------------------
//   BUTTONS
//---------------------------------------------------------------
#include <CD4021.h>

byte dataPin = 9;
byte latchPin = 8;
byte clockPin = 7;

ShiftReg buttons = ShiftReg(dataPin, latchPin, clockPin);

void testButtons() {
  for (int i = 0; i < 304; i++) {
    if (buttons.risingEdge(i)) {

      Serial.print("Key");
      Serial.print("\t");
      Serial.print("index:");
      Serial.print(i);
      Serial.print("\t");

//      String patchType = 0;
//
//      switch (nodes.[i].type) {
//        case 0:
//          patchType = "non-patch";
//        case 1:
//          patchType = "input";
//        case 2:
//          patchType = "special input";
//        case 3:
//          patchType = "output";
//
//      }

      Serial.print(nodes[i].type);
      Serial.println();

      buttons.updateLastVal(i);
    }
  }
}

//---------------------------------------------------------------
//   POTENTIOMETERS
//---------------------------------------------------------------
#include <CD4067.h>

byte selPins[3] = {15, 16, 17};
byte readPins[3] = {A3, A4, A5 };
MuxIn pots = MuxIn(selPins[0], selPins[1], selPins[2], A6, A7);

void potsInit() {
  for (int i = 0; i < 3; i++) pots.attach(readPins[i]);
  for (int i = 0; i < 200; i++)pots.update();
}

void testPots() {
  for (int i = 0; i < 26; i++) {
    if (pots.hasChanged(i)) {
      Serial.print("Pot");
      Serial.print("\t");
      Serial.print("index:");
      Serial.print(i);
      Serial.print("\t");
      Serial.println(pots.vals[i]);
      pots.updateLastVals(i);
      screenPrint(pots.vals[i]);
    }
  }
}

//---------------------------------------------------------------
//   LEDS
//---------------------------------------------------------------
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
