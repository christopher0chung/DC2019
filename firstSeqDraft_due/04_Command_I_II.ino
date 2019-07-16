struct noteNode {
  byte key;
  byte ledx;
  byte ledy;
  bool state;
  bool lastState;
  byte note;
};

noteNode piano[25] = {
  {85, 32, 3, 0, 0, 0},  {95, 32, 2, 0, 0, 0},  {86, 33, 3, 0, 0, 0},  {82, 33, 2, 0, 0, 0},  {91, 34, 3, 0, 0, 0},
  {87, 35, 3, 0, 0, 0},  {90, 35, 2, 0, 0, 0},  {81, 36, 3, 0, 0, 0},  {83, 36, 2, 0, 0, 0},  {105, 37, 3, 0, 0, 0},
  {55, 37, 2, 0, 0, 0},  {50, 38, 3, 0, 0, 0},  {47, 39, 3, 0, 0, 0},  {57, 39, 2, 0, 0, 0},  {74, 32, 7, 0, 0, 0},
  {65, 32, 6, 0, 0, 0},  {41, 33, 7, 0, 0, 0},  {51, 34, 7, 0, 0, 0},  {63, 34, 6, 0, 0, 0},  {59, 35, 7, 0, 0, 0},
  {68, 35, 6, 0, 0, 0},  {72, 36, 7, 0, 0, 0},  {70, 36, 6, 0, 0, 0},  {77, 37, 7, 0, 0, 0},  {78, 38, 7, 0, 0, 0},
};

int pitchAdjust[4];

unsigned long previousMillis = 0;
bool tog = 0;
unsigned int interval = 1000;

void autoTog() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    tog = !tog;
    piano[0].state = tog;
  }
}

void commandLeft() {
  for (int i = 0; i < 25; i++) {
    if (buttons.vals[piano[i].key] != buttons.lastVals[piano[i].key]) {
      if (buttons.vals[piano[i].key] == 1) {
        if (piano[i].state == 1) {
          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
        }
        piano[i].note = 48 + i + pitchAdjust[0];
        usbMIDI.sendNoteOn(piano[i].note, 127, 1);
        leds.drawPixel(piano[i].ledx, piano[i].ledy, 1);
      }
      else {
        if (piano[i].state == 0) {
          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
          leds.drawPixel(piano[i].ledx, piano[i].ledy, 0);
        }
      }
      buttons.lastVals[piano[i].key] = buttons.vals[piano[i].key];
    }
  }

  for (int i = 0; i < 25; i++) {
    if (piano[i].state != piano[i].lastState) {
      if (piano[i].state == 1) {
        if (buttons.vals[piano[i].key] == 1) {
          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
        }
        piano[i].note = 48 + i + pitchAdjust[0];
        usbMIDI.sendNoteOn(piano[i].note, 127, 1);
        leds.drawPixel(piano[i].ledx, piano[i].ledy, 1);
      } 
      else {
        if (buttons.vals[piano[i].key] = 0) {
          usbMIDI.sendNoteOff(piano[i].note, 0, 1);
          leds.drawPixel(piano[i].ledx, piano[i].ledy, 0);
        }
      }
      piano[i].lastState = piano[i].state;
    }
  }
}
