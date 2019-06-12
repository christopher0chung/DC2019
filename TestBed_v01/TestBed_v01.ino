#include <Key.h>

//-----------------------------------------------------------------------------------------------------------
// Region - Keypad
//-----------------------------------------------------------------------------------------------------------

#define I2CADDR 0x22        // address of MCP23017 chip on I2C bus

const byte ROWS_key = 8; //four rows
const byte COLS_key = 8; //three columns


//-----------------------------------------------------------------------------------------------------------
// Region - LED
//-----------------------------------------------------------------------------------------------------------

const byte ROWS_led = 8; //four rows
const byte COLS_led = 48; //three columns

//-----------------------------------------------------------------------------------------------------------
// Region - Logic
//-----------------------------------------------------------------------------------------------------------

const byte INPUTS_MAX = 64;
const byte OUTPUTS_MAX = 16;

//-----------------------------------------------------------------------------------------------------------
// Region - Model
//-----------------------------------------------------------------------------------------------------------

KeyState Model_Key_Current [ROWS_key][COLS_key] = {
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE}
};

KeyState Model_Key_Last [ROWS_key][COLS_key] = {
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE},
  {IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE}
};

bool Model_LED [ROWS_led][COLS_led];
