#include <CD4021.h>

ShiftReg keys = ShiftReg(6, 5, 4);

void setup() {

}

void loop() {
keys.update();

  for (int i=0; i<keys.chips; i++) {
    for (int v=0; v<keys.registers; v++) {
      if (keys.vals[i][v] != keys.lastVals[i][v]) {
        Serial.print(keys.vals[i][v]);
        Serial.print("\t");
        Serial.print(i);
        Serial.print("\t");
        Serial.print(v);
        Serial.println();
        keys.lastVals[i][v] = keys.vals[i][v];
      }
    }
  }
}
