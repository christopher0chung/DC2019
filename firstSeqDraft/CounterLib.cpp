//-----------------------------------------------------------------------------------------------------------
//   COUNTER_LOGIC
//-----------------------------------------------------------------------------------------------------------
#include "CounterLib.h"

//-----------------------------------------------------------------------------------------------------------
//   PUBLIC
//-----------------------------------------------------------------------------------------------------------

Counter::Counter(int inputXs[6], int inputYs[6], int outputXs[16], int outputYs[16])
{
  for (int i = 0; i < 6; i++)
  {
    inputNodeXs[i] = inputXs[i];
    inputNodeYs[i] = inputYs[i];
  }
  for (int i = 0; i < 16; i++)
  {
    outputNodeXs[i] = outputXs[i];
    outputNodeYs[i] = outputYs[i];
  }
}

void Counter::changeState(CounterSelect_Seq topM, CounterSelect_Seq botM)
{
  topMode = topM;
  bottomMode = botM;

  if (topMode == bottomMode)
  {
    if (topMode == Forward)
    {
      topModulo = 0;
      bottomModulo = 0;
      unifiedModulo = 16;
    }
    else if (topMode == PingPong)
    {
      topModulo = 0;
      bottomModulo = 0;
      unifiedModulo = 15;
    }
  }
  masterCounter = 0;
}

void Counter::tick(bool m[8][8])
{
  counter();
  logic(m);
}

//-----------------------------------------------------------------------------------------------------------
//   PRIVATE
//-----------------------------------------------------------------------------------------------------------
void Counter::counter()
{
  masterCounter = (masterCounter + 1) % 2147483647;
  topCounter = masterCounter % topModulo;
  bottomCounter = masterCounter % bottomModulo;
  unifiedCounter = masterCounter % unifiedModulo;
}
void Counter::logic(bool m[8][8])
{
  // Mirrored modes
  if (topMode == bottomMode)
  {
    if (topMode == Forward)
    {
      for (int i = 0; i < 16; i++)
      {
        if (i == unifiedCounter)
          m[outputNodeYs[i]][outputNodeXs[i]] = true;
        else
          m[outputNodeYs[i]][outputNodeXs[i]] = false;
      }
    }
    else if (topMode == PingPong)
    {
      if (unifiedCounter == 0)
        pingOrPong = !pingOrPong;
      for (int i = 0; i < 16; i++)
      {
        if (i == unifiedCounter)
        {
          if (pingOrPong)
            m[outputNodeYs[i]][outputNodeXs[i]] = true;
          else
            m[outputNodeYs[unifiedModulo - i]][outputNodeXs[unifiedModulo - i]] = true;
        }
        else
        {
          if (pingOrPong)
            m[outputNodeYs[i]][outputNodeXs[i]] = false;
          else
            m[outputNodeYs[unifiedModulo - i]][outputNodeXs[unifiedModulo - i]] = false;
        }
      }
    }
  }
}
