#ifndef CD4021_h
#define CD4021_h
#include "Arduino.h"

class ShiftReg {
  public:
    ShiftReg(byte _dataPin, byte _latchPin, byte _clockPin);

    byte chips;
    byte registers;
      
    byte dataPin;
    byte latchPin;
    byte clockPin;

    bool vals[304];
    bool lastVals[304];
  
    void update();  

    byte shiftIn(byte _data, byte _clock);  

    bool hasChanged(int i);
    bool risingEdge(int i);
    bool fallingEdge(int i); 

    void updateLastVals();  

  private:

};

#endif