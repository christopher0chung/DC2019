

void loop() {
  pots.update();
  keysUpdate();

  timerUpdate();
  ledsUpdate();
  leds.write();
}
