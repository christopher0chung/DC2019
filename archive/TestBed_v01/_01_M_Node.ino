class M_Node
{
  public:
    bool onOff;
    int myButtonRow;
    int myButtonCol;
    int myLEDRow;
    int myLEDCol;

    void Prep(int buttonRow, int buttonCol, int ledRow, int ledCol)
    {
      onOff = false;
      myButtonRow = buttonRow;
      myButtonCol = buttonCol;
      myLEDRow = ledRow;
      myLEDCol = ledCol;
    }

    void TurnOn()
    {
      onOff = true;
    }

    void TurnOff()
    {
      onOff = false;
    }

  private:
};

class M_Node_Output : public M_Node
{

};

class M_Node_Input : public M_Node
{
  public:
    M_Node_Output inputs[8];
};
