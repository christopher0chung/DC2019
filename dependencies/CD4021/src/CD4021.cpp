#include "Arduino.h"
#include "CD4021.h"

ShiftReg::ShiftReg(byte _dataPin, byte _latchPin, byte _clockPin) {
  chips = 38;
  registers = 8;
  
  dataPin = _dataPin;
  latchPin = _latchPin;
  clockPin = _clockPin;
  pinMode(dataPin, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void ShiftReg::update() {

  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);

  for (int c = 0; c < chips; c++) {

    byte regVal = 0;
    regVal = shiftIn(dataPin, clockPin);

    for (int r = 0; r < registers; r++) {

      int loc = r + c*8;

      if (regVal & (1 << r) ) {
        vals[loc] = 1;
      }
      else {
        vals[loc] = 0;
      }
      
    }
  }
}

byte ShiftReg::shiftIn(byte _data, byte _clock) {
  byte data = 0;
  for (int i = 7; i >= 0; i--) {
    digitalWrite(_clock, 0);
    delayMicroseconds(2);
    int temp = digitalRead(_data);
    if (temp) {
      data = data | (1 << i);
    }
    digitalWrite(_clock, 1);
  }
  return data;  
}

bool ShiftReg::hasChanged(int loc)  {
  if (vals[loc] != lastVals[loc]) {
    return 1;
  }
  else {
    return 0;
  }
}

void ShiftReg::updateLastVals(int loc) {
  lastVals[loc] = vals[loc];
}