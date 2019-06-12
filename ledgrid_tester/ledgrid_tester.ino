#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 20;
int numberOfHorizontalDisplays = 6;
int numberOfVerticalDisplays = 1;
byte panelArrange[6] = {5, 4, 0, 1, 2, 3};
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int incomingByte = 0;
int x = 0;

void setup() {
  matrix.setIntensity(0);

  for (int i = 0; i < 6; i++) {
    matrix.setPosition(i, panelArrange[i], 0);
    matrix.setRotation(i, 3);
  }

}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 97) {
      Serial.println(x);
      matrix.fillScreen(0);
      matrix.drawPixel(x, 7, HIGH);
      matrix.write();
      x++;
    }
  }
}
