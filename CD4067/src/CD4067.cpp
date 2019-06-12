#include "Arduino.h"
#include "CD4067.h"

MuxIn::MuxIn(byte _selPin1, byte _selPin2, byte _selPin4, byte _selPin8, byte _smoothSel) {
  numMux = 0;                                           // This number increases by 1 with each attach() method used
  
  smoothAmount = .5;                                    // Default amount of smoothing
  smoothSel = _smoothSel;                               // Toggles smoothing
  if (smoothSel > 1 || smoothSel < 0) {                 // Set smoothSel to 0 if improper input received
    smoothSel = 0;
  }

  selPins[0] = _selPin1;                                // Assign selection pins to variables
  selPins[1] = _selPin2;
  selPins[2] = _selPin4;
  selPins[3] = _selPin8;
  for (int i = 0; i < sizeof(selPins); i++) {           // Each selPins[] designated as OUTPUT
    pinMode(selPins[i], OUTPUT);
  }
}

void MuxIn::attach(byte _pin) {
  inputPins[numMux] = _pin;                              // Put assigned input pin into an array
  pinMode(inputPins[numMux], INPUT);                     // The new input pin is designated as an INPUT
  numMux++;                                              // Advance one step in array for next usage of attach() method
}

void MuxIn::refresh() {
  for (int x = 0; x<muxChannels; x++) {                  // Stepping through the channels allows for changing selPins[] less often
    for (int y = 0; y <numMux; y++) {                    // numMux taken from how many times attach method was used
      int rawVal;                                        // Local variable to store value of incoming reading
        rawVal = analogRead(inputPins[y]);               // Take the reading
        if (smoothSel) {                                 // Is smoothing enabled?
          finalVals[y][x] = smooth(rawVal, smoothAmount, finalVals[y][x]);
        }
        else {
          finalVals[y][x] = rawVal;
        }
    }
    digitalWrite(selPins[changePins[x]], changeVals[x]); // Change the selection pins based on the two Gray Code arrays
  }
}

int MuxIn::getReading(byte _mux, byte _channel) {
  return finalVals[_mux][_channel];                      // Return a value from the finalVals[][] array
}

// smooth   v0.2 by Paul Badger 2007 - http://playground.arduino.cc/Main/Smooth
int MuxIn::smooth(int data, float filterVal, float smoothedVal) {
  if (filterVal > 1) filterVal = .99;
  else if (filterVal <= 0) filterVal = 0;
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}