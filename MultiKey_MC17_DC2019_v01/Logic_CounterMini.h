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
    void Tick();
    enum Input_Aux{Aux_Inc, Aux_Dec, Aux_Hold, Aux_Pause};

    unsigned int rate;
    unsigned int timer;

  private:
    int _counterIndex;
 };

 #endif
