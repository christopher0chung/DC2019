class C_Logic_Counter : C_Logic
{
  public:
    int counter_True;
    int counter_Unified;

    void Prep(M_Node_Input inc, M_Node_Input dec, M_Node_Input rst, M_Node_Input hld, M_Node_Input pse, M_Node_Input clr,
              M_Node_Output o0, M_Node_Output o1, M_Node_Output o2, M_Node_Output o3, M_Node_Output o4, M_Node_Output o5, M_Node_Output o6, M_Node_Output o7, M_Node_Output o8, M_Node_Output o9, M_Node_Output o10, M_Node_Output o11, M_Node_Output o12, M_Node_Output o13, M_Node_Output o14, M_Node_Output o15)
    {
      RegisterInput(inc);
      RegisterInput(dec);
      RegisterInput(rst);
      RegisterInput(hld);
      RegisterInput(pse);
      RegisterInput(clr);

      RegisterOutput(o0);
      RegisterOutput(o1);
      RegisterOutput(o2);
      RegisterOutput(o3);
      RegisterOutput(o4);
      RegisterOutput(o5);
      RegisterOutput(o6);
      RegisterOutput(o7);
      RegisterOutput(o8);
      RegisterOutput(o9);
      RegisterOutput(o10);
      RegisterOutput(o11);
      RegisterOutput(o12);
      RegisterOutput(o13);
      RegisterOutput(o14);
      RegisterOutput(o15);
    }

    void Update()
    {
      //stuff in between ticks w a bool check if nothing is req'd
    }

    void Tick()
    {
      _CountersUpdate();
      _InputsUpdate();
      _OutputsUpdate();
      _ModelUpdate();
    }

  private:
    void _CountersUpdate()
    {
      counter_True = (counter_True + 1) % 2147483647;
      counter_Unified = counter_True % 16;
    }

    void _InputsUpdate()
    {

    }

    void _OutputsUpdate()
    {
      Serial.println(counter_Unified);
      for (int i = 0; i < outputsCount; i++)
      {
        if (i != counter_Unified)
          outputs[i].TurnOff();
        else
          outputs[i].TurnOn();
      }
    }

    void _ModelUpdate()
    {
      for (int i = 0; i < outputsCount; i++)
      {
        Model_LED[outputs[i].myLEDRow][outputs[i].myLEDCol] = outputs[i].onOff;
      }
    }
};

//enum CounterSelect_Type {Sequence, Subdivider, Divider, Binary};
//enum CounterSelect_Seq {Forward = 16, PingPong = 15, Brownian = 2147483647, Random = 2147483647};
//enum CounterSelect_Subd {Two = 16, Three = 27, Four = 16, Random = 2147483647};
//enum CounterSelect_Div {Squared = 65536, Cubed = 384, Even = 16, Odd = 16};
//enum CounterSelect_Bin {Squared = 256, Cubed = 256, Prime = 256, Seidel = 256};
