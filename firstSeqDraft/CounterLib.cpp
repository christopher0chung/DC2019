//-----------------------------------------------------------------------------------------------------------
//   COUNTER_LOGIC
//-----------------------------------------------------------------------------------------------------------
#include "CounterLib.h"

//-----------------------------------------------------------------------------------------------------------
//   PUBLIC
//-----------------------------------------------------------------------------------------------------------

//  Array size declaration required because class will continuously require these values and so it makes
//    sense to pass the values in. Because arrays cannot be copied, their values are transcribed.
//  The size requirements to the array parameters should prevent arrays of unexpected ranges from being passed
//    to the class.

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

//  changeState will store the value of the top and bottom for comparison. Intentionally stores both the mode
//    and modulo values to prevent confusion if different modes have the same sequence length.
//  Changing either state should reset the main counter so only a single function is written.
//  Functions to singly change the top and bottom modes can leverage this same 'changeState' function because
//    CounterLib internally stores the top and bottom modes for assessment. [Examples included]

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
  pingOrPong = true;
}

void Counter::changeTopState(CounterSelect_Seq newTopMode)
{
  changeState(newTopMode, bottomMode);
}

void Counter::changeBottomState(CounterSelect_Seq newBottomMode)
{
  changeState(topMode, newBottomMode);
}

//  tick is the simplifed public function for something like COUNTER to call.
//  In order to tick to be useful in a library, it has to have access to the model that it will change. To
//    that end, the entire model is passed by reference. [NOTE] according to arduino forum posts, passing
//    an array using only its name will inform the compiler to pass by reference by default.
//  When a multidimensional array is passed by reference, the first index can be left blank, but all
//    subsequent index dimensions must be defined. I have no idea why.

void Counter::tick(bool m[][8])
{
  counter();
  logic(m);
}

//-----------------------------------------------------------------------------------------------------------
//   PRIVATE
//-----------------------------------------------------------------------------------------------------------
void Counter::counter()
{
  masterCounter = (masterCounter + 1) % 2147483647;     //  Modulo prevents master counter from becoming (-).
  topCounter = masterCounter % topModulo;               //  Rolling over the masterCounter may have weird 
  bottomCounter = masterCounter % bottomModulo;         //    effect. Not tested. Shouldn't matter.
  unifiedCounter = masterCounter % unifiedModulo;
}
void Counter::logic(bool m[][8])
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
      //  PingPong requires an additional pingOrPong boolean so that directionality can be assigned.
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
