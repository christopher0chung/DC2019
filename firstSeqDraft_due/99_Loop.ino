



void loop() {
  buttons.update();
  pots.update();
  //    testButtons();
  //    testPots();

  autoTog();
  commandLeft();

  commandPotsUpdate();

  leds.write();
}
