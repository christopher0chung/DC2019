/*
  Counter Module - Test For Mini Board
  Each half of the test bed will be independent
  Features - Inc, Dec, Hold, Pause
*/

#ifndef CounterMini_h
#define CounterMini_h

#include Arduino.h //Temp inclusion

class CounterMini
{
  public:
    CounterMini(int index, unsigned int startingRate);
    void WriteToAux_Buffered(Input_Aux inputNode, bool highLow);
    void WriteToAux_Unbuffered(Input_Aux inputNode, bool highLow);
    void Update(unsigned int deltaTime);
    void UpdateRate(unsigned int newRate);
    void UpdateMode(Output_Mode newMode);
    enum Input_Aux {Inc, Dec, Hld, Pse};
    enum OutputMode {One, Two];
    Output_Mode currentMode;
    void Increment();
    void Decrement();
    bool activeValues[4];
    bool outputNodes[8];


  private:
    int _counterIndex;
    unsigned int _rate;
    unsigned int _timer;
    bool _bufferValues[4];
    bool _lastValues[4];
};

#endif
