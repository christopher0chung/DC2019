class C_Logic
{
  public:
    M_Node_Input *inputs [INPUTS_MAX];
    M_Node_Output *outputs[OUTPUTS_MAX];
    int inputsCount = 0;
    int outputsCount = 0;

    void RegisterInput(M_Node_Input newInput)
    {
      if (inputsCount < INPUTS_MAX)
      {
        inputs[inputsCount] = &newInput;
        inputsCount++;
      }
    }

    void RegisterOutput(M_Node_Output newOutput)
    {
      if (outputsCount < OUTPUTS_MAX)
      {
        outputs[outputsCount] = &newOutput;
        outputsCount++;
      }
    }

  private:
};
