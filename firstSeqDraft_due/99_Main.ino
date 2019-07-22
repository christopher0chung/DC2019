

void setup() {
  //  Serial.begin(9600);
  linkageInit();
  potsInit();
  ledsInit();
  screenInit();
}

void loop() {

  buttons.update();
  pots.update();
  //    testButtons();
  //    testPots();
//  autoTog();
  commandLeft();
  commandPotsUpdate();
  leds.write();

}
