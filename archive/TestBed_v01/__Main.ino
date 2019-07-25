//-----------------------------------------------------------------------------------------------------------
// Region - Class References
//-----------------------------------------------------------------------------------------------------------

C_Input_Keys keys00 = C_Input_Keys(); // can now have multiple keypads
C_Logic_Counter counter00 = C_Logic_Counter();
V_Output_LEDs leds00 = V_Output_LEDs();

//-----------------------------------------------------------------------------------------------------------
// Region - Main Functions
//-----------------------------------------------------------------------------------------------------------

void setup()
{
  keys00.Prep();
  MapNodes();
  counter00.Prep(&inc_1, &dec_1, &rst_1, &hld_1, &pse_1, &clr_1, 
  &o0_1, &o1_1, &o2_1, &o3_1, &o4_1, &o5_1, &o6_1, &o7_1, &o8_1, &o9_1, &o10_1, &o11_1, &o12_1, &o13_1, &o14_1, &o15_1);
  leds00.Prep();
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
      if (Model_Key_Last[i][j] != Model_Key_Current[i][j])
      {
        Serial.print(keys00.keymap[i][j]);
        Serial.println(" has changed state");
      }
    }
  }

  //KeepTrackOfTimeAndTick();
}

unsigned long lastMicros;
unsigned long thisMicros;
unsigned long delMicros;
unsigned long timer;

//void KeepTrackOfTimeAndTick()
//{
//  lastMicros = thisMicros;
//  thisMicros = micros();
//  delMicros = thisMicros - lastMicros;
//
//  timer += delMicros;
//  if (timer >= 500000)
//  {
//    timer -= 500000;
//    counter00.Tick();
//    leds00.Update();
//    Serial.println(counter00.counter_Unified);
//  }
//}
