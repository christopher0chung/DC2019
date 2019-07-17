#ifndef CD4067_h
#define CD4067_h
#include "Arduino.h"


const byte muxChannels = 8;                                     // The 4051 multiplexer has 8 channels
const byte changePins[] = {0, 1, 0, 2, 0, 1, 0, 2};
const boolean changeVals[] = {1, 1, 0, 1, 1, 0, 0, 0};

class MuxIn {
  public:
    MuxIn(byte _selPinA, byte _selPinB, byte _selPinC, byte _anaPin1, byte _anaPin2);
   
    byte numMux;                // This number starts at 0 and increases by 1 with each .attach method   
    float smoothAmount;         // Sets the amount of smoothing applied to signal
    byte inputPins[3];          // Pins connected to the analog output of each 4051
    byte selPins[3];            // Connected to digital outputs of microcontroller. Determines channel selection
    byte anaPin1;
    byte anaPin2;
    int smoothVals[26];
    int vals[26];
    int lastVals[26];
  
    void attach(byte _pin);                   // Associate microcontroller pin with a Modi multiplexer
    void update();                                            // Capture readings from all controllers
    int smooth(int data, float filterVal, float smoothedVal);  
    bool hasChanged(int loc); 
    void updateLastVals(int loc);  

  private:
};

#endif
