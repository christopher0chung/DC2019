struct node {
  int  key;
  byte ledx;
  byte ledy;
};

node commandController[4] {
  {285, 27, 7},
  {301, 28, 7},
  {302, 29, 7},
  {296, 30, 7},
};

byte mode = 4;
String modeScreenText[5] = {"VEL", "LEN", "PICH", "CC", " "};

int potArray[4] = {21, 15, 22, 20};
byte lastccVal[4];

void commandPotsUpdate() {
  for (int i = 0; i < 4; i++) {
    if (buttons.hasChanged(commandController[i].key)) {
      if (buttons.vals[commandController[i].key] == 1) {
        if (mode == i) {
          leds.drawPixel(commandController[i].ledx, commandController[i].ledy, 0);
          mode = 4;
          screenPrint(modeScreenText[i]);
        }
        else {
          leds.drawPixel(commandController[mode].ledx, commandController[mode].ledy, 0);
          leds.drawPixel(commandController[i].ledx, commandController[i].ledy, 1);
          mode = i;
          screenPrint(modeScreenText[i]);
        }
      }
      buttons.updateLastVals(commandController[i].key);
    }
  }

  for (int i = 0; i < 4; i++) {
    if (pots.hasChanged(potArray[i])) {

      switch (mode) {
        case 0: {
            int vel = pots.vals[potArray[i]];
            vel = map(vel, 5, 150, 0, 127);
            vel = constrain(vel, 0, 127);

            if (vel != velAdjust[i]) {
              velAdjust[i] = vel;
              screenPrint(vel);
            }
          }
          break;

        case 1: {
            int noteLength = pots.vals[potArray[i]];
            noteLength = map(noteLength, 5, 150, 10, 3000);
            noteLength = constrain(noteLength, 10, 3000);

            if (noteLength != lengthAdjust[i]) {
              lengthAdjust[i] = noteLength;
              screenPrint(noteLength);
            }
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

        case 4: {
          }
          break;
      }
      pots.updateLastVals(potArray[i]);
    }
  }
}
