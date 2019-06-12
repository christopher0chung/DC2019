//-----------------------------------------------------------------------------------------------------------
// Region - Class References
//-----------------------------------------------------------------------------------------------------------

C_Input_Keys keys00 = C_Input_Keys(); // can now have multiple keypads

V_Output_LEDs leds00 = V_Output_LEDs();

//-----------------------------------------------------------------------------------------------------------
// Region - Main Functions
//-----------------------------------------------------------------------------------------------------------

void setup()
{
  keys00.Prep();
}

void loop()
{
  keys00.Update();
  keys00.StoreModel();
  keys00.PrimeModel();
  keys00.UpdateModel();

  for (int i = 0; i < ROWS_key; i++)
  {
    for (int j = 0; j < COLS_key; j++)
    {
      if(Model_Key_Last[i][j] != Model_Key_Current[i][j])
      {
        Serial.print(keys00.keymap[i][j]);
        Serial.println(" has changed state");
      }
    }
  }

}
