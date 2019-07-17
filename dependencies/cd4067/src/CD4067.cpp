#include "Arduino.h"
#include "CD4067.h"

MuxIn::MuxIn(byte _selPinA, byte _selPinB, byte _selPinC, byte _anaPin1, byte _anaPin2) {
  numMux = 0;                                           // This number increases by 1 with each attach() method used        
  smoothAmount = .9;                                    // Default amount of smoothing
  
  selPins[0] = _selPinA;                                // Assign selection pins to variables
  selPins[1] = _selPinB;
  selPins[2] = _selPinC; 

  anaPin1 = _anaPin1;
  anaPin2 = _anaPin2;


  for (int i=0; i<3; i++) {               // Each selPins[] designated as OUTPUT
    pinMode(selPins[i], OUTPUT); 
  }
}

void MuxIn::attach(byte _pin) { 
  inputPins[numMux] = _pin;                              // Put assigned input pin into an array
  pinMode(inputPins[numMux], INPUT);                     // The new input pin is designated as an INPUT
  numMux++;                                              // Advance one step in array for next usage of attach() method
}

void MuxIn::update() {
  for (int x=0; x<muxChannels; x++) {                    
    for (int y=0; y<numMux; y++) {    

      int loc = x + y*8;

      int rawVal;                                             
      rawVal = analogRead(inputPins[y]);

      if (rawVal > smoothVals[loc] + 4  || rawVal < smoothVals[loc] - 4) {     
        smoothVals[loc] = smooth(rawVal/6, smoothAmount, smoothVals[loc]);
        vals[loc] = smooth(smoothVals[loc], smoothAmount, vals[loc]);
      }

    }

    digitalWrite(selPins[changePins[x]], changeVals[x]); 

  }
  
  int rawVal;                                          
  rawVal = analogRead(anaPin1);
  if (rawVal > smoothVals[24] + 4  || rawVal < smoothVals[24] - 4) {     
    smoothVals[24] = smooth(rawVal/6, smoothAmount, smoothVals[24]);
    vals[24] = smooth(smoothVals[24], smoothAmount, vals[24]);
  }
                                         
  rawVal = analogRead(anaPin2);
  if (rawVal > smoothVals[25] + 4  || rawVal < smoothVals[25] - 4) {     
    smoothVals[25] = smooth(rawVal/6, smoothAmount, smoothVals[25]);
    vals[25] = smooth(smoothVals[25], smoothAmount, vals[25]);
  }
}

int MuxIn::smooth(int data, float filterVal, float smoothedVal) {
  if (filterVal > 1) filterVal = .99;
  else if (filterVal <= 0) filterVal = 0;
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal *  filterVal);
  return (int)smoothedVal;
}

bool MuxIn::hasChanged(int loc)  {
  if (vals[loc] != lastVals[loc]) {
    return 1;
  }
  else {
    return 0;
  }
}

void MuxIn::updateLastVals(int loc) {
  lastVals[loc] = vals[loc];
}