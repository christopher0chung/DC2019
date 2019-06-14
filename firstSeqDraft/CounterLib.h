//-----------------------------------------------------------------------------------------------------------
//   COUNTER_LOGIC
//-----------------------------------------------------------------------------------------------------------

#ifndef CounterLib_h
#define CounterLib_h

enum CounterSelect_Seq {Forward, PingPong, Brownian, Random};
//enum CounterSelect_Seq {Forward = 16, PingPong = 15, Brownian = 2147483647, Random = 2147483647};

class Counter
{
  public:
    Counter(int inputXs[6], int inputYs[6], int outputXs[16], int outputYs[16]);
  
    int masterCounter;
    int topCounter;
    int bottomCounter;
    int unifiedCounter;

    int topModulo;
    int bottomModulo;
    int unifiedModulo;

    CounterSelect_Seq topMode;
    CounterSelect_Seq bottomMode;

    void changeState(CounterSelect_Seq, CounterSelect_Seq);
    void tick(bool m[8][8]);

  private:
    int inputNodeXs[6];
    int inputNodeYs[6];
    int outputNodeXs[16];
    int outputNodeYs[16];

    bool pingOrPong;

    void counter();
    void logic(bool m[8][8]);
};

#endif
