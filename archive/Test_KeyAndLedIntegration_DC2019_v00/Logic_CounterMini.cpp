#include "Arduino.h"
#include "Logic_CounterMini.h"

Logic_CounterMini::Logic_CounterMini(int index)
{
  _counterIndex = index;
}

void WriteToAux_Buffered(Input_Aux inputNode, bool highLow)
{
  _bufferValues[inputNode] = highLow;
}
void WriteToAux_Unbuffered(Input_Aux inputNode, bool highLow)
{
  activeValues[inputNode] = highLow;
}
void Update(unsigned int deltaTime)
{
  _timer += deltaTime;
  if (_timer >= _rate)
  {
    _timer -= _rate;

    // Assess and update pause
    // --------------------------------------------------------------------
    // If the value changed from the last frame:
    //  As it goes low to hi - toggle pause state
    // Update last val to buffered val
    // --------------------------------------------------------------------
    if (_lastValues[Input_Aux.Pse] != _bufferedValues[Input_Aux.Pse])
    {
      if (_bufferedValues[Input_Aux.Pse])
      {
        activeValues[Input_Aux.Pse] = !activeValues[Input_Aux.Pse];
      }
      _lastValues[Input_Aux.Pse] = _bufferedValues[Input_Aux.Pse];
    }

    // Assess and update hold
    // --------------------------------------------------------------------
    // Buffer value updated to active and last
    // --------------------------------------------------------------------
    if (_lastValues[Input_Aux.Pse] != _bufferedValues[Input_Aux.Pse])
    {
      activeValues[Input_Aux.Pse] = _bufferedValues[Input_Aux.Pse];
      _lastValues[Input_Aux.Pse] = _bufferedValues[Input_Aux.Pse];
    }

    //Increment Check -- before buffer update
    // --------------------------------------------------------------------
    // If aux increment is buffered:
    //  Call Increment and update
    // --------------------------------------------------------------------

    if (_lastValues[Input_Aux.Inc] != _bufferedValues[Input_Aux.Inc])
    {
      if (_bufferedValues[Input_Aux.Inc])
        Increment();
      activeValues[Input_Aux.Inc] = _bufferedValues[Input_Aux.Inc];
      _lastValues[Input_Aux.Inc] = _bufferedValues[Input_Aux.Inc];
    }

    //Decrement Check -- before buffer update
    // --------------------------------------------------------------------
    // If aux increment is buffered:
    //  Call Increment and update
    // --------------------------------------------------------------------

    if (_lastValues[Input_Aux.Dec] != _bufferedValues[Input_Aux.Dec])
    {
      if (_bufferedValues[Input_Aux.Dec])
        Decrement();
      activeValues[Input_Aux.Dec] = _bufferedValues[Input_Aux.Dec];
      _lastValues[Input_Aux.Dec] = _bufferedValues[Input_Aux.Dec];
    }


    //Roll over increment -- after buffer update
    if (!activeValues[Input_Aux.Hld] && !activeValues[Input_Aux[Pse])
        Increment();
  }
}
void UpdateRate(unsigned int newRate)
{
  _rate = newRate;
}

void Increment()
{
  if (currentMode == OutputMode.One)
  {
    for (int i = 0; i < sizeof(outputNodes); i++)
    {
      outputNodes[(i + 1) % sizeof(outputNodes)] = outputNodes[i];
    }
  }
  else
  {
    // update and rollover top half
    for (int i = 0; i < sizeof(outputNodes) / 2; i++)
    {
      outputNodes[(i + 1) % (sizeof(outputNodes) / 2)] = outputNodes[i];
    }

    // mirror bottom half
    for (int i = 0; i < sizeof(outputNodes) / 2; i++)
    {
      outputNodes[i + (sizeof(outputNodes) / 2)] = outputNodes[i];
    }
  }
}

void Decrement()
{
  if (currentMode == OutputMode.One)
  {
    for (int i < sizeof(outputNodes) - 1; i >= 0; i--)
    {
      outputNodes[(i + sizeof(outputNodes) - 1) % sizeof(outputNodes)] = outputNodes[i];
    }
  }
  else
  {
    // update and rollover top half
    for (int i = 0; i < sizeof(outputNodes) / 2; i++)
    {
      outputNodes[(i + 1) % (sizeof(outputNodes) / 2)] = outputNodes[i];
    }

    // mirror bottom half
    for (int i = 0; i < sizeof(outputNodes) / 2; i++)
    {
      outputNodes[i + (sizeof(outputNodes) / 2)] = outputNodes[i];
    }
  }
}
void UpdateMode(Output_Mode newMode)
{

}
