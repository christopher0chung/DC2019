// led libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

class V_Output_LEDs
{
  public:
    int pinCS = 20; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
    int numberOfHorizontalDisplays = 1;
    int numberOfVerticalDisplays = 1;

    Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

    //-----------------------------------------------------------------------------------------------------------
    // Region - Test Functions
    //-----------------------------------------------------------------------------------------------------------

    bool ledModel[ROWS_led][COLS_led];

    void Prep()
    {
      
    }

    void Update()
    {
      
    }

  private:
};
