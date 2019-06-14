#ifndef CD4067_h
#define CD4067_h
#include "Arduino.h"

const byte muxChannels = 16;                                     // The 4067 multiplexer has 16 channels
const byte changePins[] = {0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 3};
const boolean changeVals[] = {1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0};

class MuxIn {
  public:
    MuxIn(byte _selPinA, byte _selPinB, byte _selPinC, byte _selPinD, byte _smoothSel);
   
    byte numMux;                // This number starts at 0 and increases by 1 with each .attach method   
    float smoothAmount;         // Sets the amount of smoothing applied to signal
    boolean smoothSel;          // Determines whether to smooth incoming signals or not
    byte inputPins[2];          // Pins connected to the analog output of each 4051
    byte selPins[4];            // Connected to digital outputs of microcontroller. Determines channel selection
    int finalVals[2][16];
  
    void attach(byte _pin);                                     // Associate microcontroller pin with CD4067
    void update();                                            // Capture readings from all controllers
    int read(byte _mux, byte _channel);                  // Access a reading from finalVals[]
    int smooth(int data, float filterVal, float smoothedVal);  // Method for smoothing incoming readings
  private:
};

#endif