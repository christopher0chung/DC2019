// keypad libraries
#include <Keypad.h>
#include <Keypad_MC17.h>    // I2C i/o library for Keypad
#include <Wire.h>           // I2C library for Keypad_MC17
// led libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define I2CADDR 0x20        // address of MCP23017 chip on I2C bus

//-----------------------------------------------------------------------------------------------------------
// Region - Keypad variables and init
//-----------------------------------------------------------------------------------------------------------

const byte ROWS = 4; //four rows
const byte COLS = 8; //three columns
char keys[ROWS][COLS] = {
  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
  {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'},
  {'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
  {'0', '1', '2', '3', '4', '5', '6', '7'}
};
byte rowPins[ROWS] = {8, 9, 10, 11}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {0, 1, 2, 3, 4, 5, 6, 7}; //connect to the column pinouts of the kpd

// modify constructor for I2C i/o
Keypad_MC17 kpd = Keypad_MC17( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );

//-----------------------------------------------------------------------------------------------------------
// Region - LED variables and init
//-----------------------------------------------------------------------------------------------------------

int pinCS = 20; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

//-----------------------------------------------------------------------------------------------------------
// Region - Test Functions
//-----------------------------------------------------------------------------------------------------------

const int xSize = 8;
const int ySize = 3;
bool ledModel[xSize][ySize];

//-----------------------------------------------------------------------------------------------------------
// Region - Functions
//-----------------------------------------------------------------------------------------------------------

void setup() {
  // Keypad setup
  Serial.begin(9600);
  kpd.begin( );            // also starts wire library
  kpd.setDebounceTime(1);

  // LED setup
  matrix.setIntensity(0); // Set brightness between 0 and 15
  matrix.fillScreen(0);
  UpdateLEDs(0);
}

int ledX = 0;
int ledY = 0;

void loop() {

  if (kpd.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if (kpd.key[i].kstate == PRESSED)
      {
        if (kpd.key[i].kchar == 'j')
        {
          ledY += ySize - 1;
          ledY = ledY % ySize;
        }
        if (kpd.key[i].kchar == 'r')
        {
          ledY++;
          ledY = ledY % ySize;
        }

        if (kpd.key[i].kchar == 'q')
        {
          ledX += xSize - 1;
          ledX = ledX % xSize;
        }
        if (kpd.key[i].kchar == 's')
        {
          ledX++;
          ledX = ledX % xSize;
        }
        UpdateLEDs(i);
      }
    }
  }
}  // End loop

void UpdateLEDs(int i)
{
  int theInt = i;
  Serial.print("X:");
  Serial.print(ledX);
  Serial.print(" Y:");
  Serial.print(ledY);
  Serial.print(" character:");
  Serial.println(kpd.key[theInt].kchar);

  ledModel[ledX][ledY] = !ledModel[ledX][ledY];
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      matrix.drawPixel(j, i, ledModel[i][j]);
    }
  }
  //matrix.drawPixel(ledY, ledX, !LOW); // Draw the head of the snake
  matrix.write(); // Send bitmap to display
}
