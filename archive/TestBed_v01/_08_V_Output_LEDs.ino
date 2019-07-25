// led libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

class V_Output_LEDs
{
  public:
    int pinCS = 20; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
    int numberOfHorizontalDisplays = 6;
    int numberOfVerticalDisplays = 1;
    byte panelArrange[6] = {5, 4, 0, 1, 2, 3};

    int incomingByte = 0;
    int x = 0;

    Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

    //-----------------------------------------------------------------------------------------------------------
    // Region - Test Functions
    //-----------------------------------------------------------------------------------------------------------

    bool ledModel[ROWS_led][COLS_led];

    void Prep()
    {
      // LED setup
      matrix.setIntensity(0); // Set brightness between 0 and 15
      matrix.fillScreen(0);
      for (int i = 0; i < 6; i++) {
        matrix.setPosition(i, panelArrange[i], 0);
        matrix.setRotation(i, 3);
      }

      for (int i = 0; i < ROWS_led; i++)
      {
        for (int j = 0; j < COLS_led; j++)
        {
          Model_LED[i][j] = false;
        }
      }

      matrix.drawPixel(0, 0, HIGH);
      matrix.write();
    }

    void Update()
    {
      for (int i = 0; i < ROWS_led; i++)
      {
        for (int j = 0; j < COLS_led; j++)
        {
          matrix.drawPixel(i, j, Model_LED[i][j]);
        }
      }
      matrix.write();
    }

  private:
};
