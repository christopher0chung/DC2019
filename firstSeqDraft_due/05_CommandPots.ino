struct commandPots {
  int key;
  byte ledx;
  byte ledy;
};

commandPots commandController[4] {
  {285, 27, 7},
  {301, 28, 7},
  {302, 29, 7},
  {296, 30, 7},
};

byte mode;

int potArray[4] = {21, 15, 22, 20};
byte lastccVal[4];
int lastAdjVal[4];

void commandPotsUpdate() {
  for (int i = 0; i < 4; i++) {
    if (buttons.vals[commandController[i].key] != buttons.lastVals[commandController[i].key]) {
      leds.drawPixel(commandController[mode].ledx, commandController[mode].ledy, 0);
      leds.drawPixel(commandController[i].ledx, commandController[i].ledy, 1);
      mode = i;
    }
  }

  for (int i = 0; i < 4; i++) {
    if (pots.vals[potArray[i]] != pots.lastVals[potArray[i]]) {

      switch (mode) {
        case 0: {

          }
          break;

        case 1: {

          }
          break;

        case 2: {
            int adj = pots.vals[potArray[i]];
            adj = map(adj, 5, 150, -24, 24);
            adj = constrain(adj, -24, 24);

            if (adj != pitchAdjust[i]) {
              pitchAdjust[i] = adj;
              screenPrint(adj);
            }
          }
          break;

        case 3: {
            int ccVal = pots.vals[potArray[i]];
            ccVal = map(pots.vals[potArray[i]], 5, 150, 0, 127);
            ccVal = constrain(ccVal, 0, 127);

            if (ccVal != lastccVal[i]) {
              usbMIDI.sendControlChange(20 + i, ccVal, 1);
              lastccVal[i] = ccVal;
              screenPrint(ccVal);
            }
          }
          break;
      }
      pots.lastVals[i] = pots.vals[i];
    }
  }
}
