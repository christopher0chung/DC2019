

void loop() {
  pots.update();
  keysUpdate();

  timerUpdate();
  leds.write();
}
