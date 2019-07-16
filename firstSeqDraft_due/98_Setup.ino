
void setup() {
  //  Serial.begin(9600);
  potsInit();
  ledsInit();
  screenInit();

  for (int i = 0; i < 200; i++) {
    pots.update();
  }

}
